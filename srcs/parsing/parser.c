/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:18:34 by seruiz            #+#    #+#             */
/*   Updated: 2021/03/20 10:56:08 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parser.h"

int	ft_cat(char *dest, char *s, int j)
{
	int	i;

	i = 0;
	while (s[i])
	{
		dest[j] = s[i];
		i++;
		j++;
	}
	return (j);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	int		j;
	size_t	str1_lenght;
	size_t	str2_lenght;

	j = 0;
	str1_lenght = ft_strlen(s1);
	str2_lenght = ft_strlen(s2);
	str = ft_managed_malloc(sizeof(char) * (str1_lenght + str2_lenght + 1));
	str[str1_lenght + str2_lenght] = '\0';
	j = ft_cat(str, s1, 0);
	j = ft_cat(str, s2, j);
	ft_managed_free(s1);
	ft_managed_free(s2);
	return (str);
}

void	ft_fill_mask(char *mask, char c, int len, t_shell_command *str_struct)
{
	while (len >= 0)
	{
		mask[len] = c;
		len--;
	}
	if (str_struct->command_mask == NULL)
		str_struct->command_mask = mask;
	else
		str_struct->command_mask = ft_strjoin_free(str_struct->command_mask, mask);
}

void	ft_fill_str(char *line, int j, int len, t_shell_command *str_struct)
{
	char	*s;
	int		x;

	x = 0;
	s = ft_managed_malloc(sizeof(char) * len + 1);
	s[len] = '\0';
	while (x < len)
	{
		s[x] = line[j];
		x++;
		j++;
	}
	if (str_struct->command_string == NULL)
		str_struct->command_string = s;
	else
		str_struct->command_string = ft_strjoin_free(str_struct->command_string, s);
}

int	ft_single_quote(char *line, int j, t_shell_command *str_struct)
{
	int		ret;
	char	*mask;

	ret = j + 1;
	while (line[ret] && line[ret] != '\'')
		ret++;
	mask = ft_managed_malloc(sizeof(char) * (ret - j));
	mask[ret - j - 1] = '\0';
	ft_fill_mask(mask, '1', ret - j - 2, str_struct);
	ft_fill_str(line, j + 1, ret - j - 1, str_struct);
	return (ret + 1);
}

int	ft_double_quote(char *line, int j, t_shell_command *str_struct)
{
	int		ret;
	char	*mask;

	ret = j + 1;
	while ((line[ret] && (line[ret] != '\"' && ret - 1 >= 0))
		|| line[ret - 1] == '\\')
		ret++;
	mask = ft_managed_malloc(sizeof(char) * (ret - j));
	mask[ret - j - 1] = '\0';
	ft_fill_mask(mask, '2', ret - j - 2, str_struct);
	ft_fill_str(line, j + 1, ret - j - 1, str_struct);
	return (ret + 1);
}

t_shell_separator	*ft_set_sep(char *line, int j)
{
	t_shell_separator			*sep;

	sep = ft_managed_malloc(sizeof(t_shell_separator));
	if (line[j] == '&' && line[j + 1] == '&')
		sep->instruction_type = SHELL_SEPARATOR_TYPE_AND;
	else if (line[j] == '|' && line[j + 1] == '|')
		sep->instruction_type = SHELL_SEPARATOR_TYPE_OR;
	else if (line[j] == ';')
		sep->instruction_type = SHELL_SEPARATOR_TYPE_END;
	else if (line[j] == '|')
		sep->instruction_type = SHELL_SEPARATOR_TYPE_PIPE;
	return (sep);
}

t_shell_command	*ft_new_str_struct(void)
{
	t_shell_command	*str_struct;

	str_struct = ft_managed_malloc(sizeof(t_shell_command));
	ft_memset(str_struct, 0, sizeof(t_shell_command));
	str_struct->instruction_type = SHELL_INSTRUCTION_COMMAND;
	return (str_struct);
}

int	ft_separator(char *line, t_node_binary **root, int j, t_shell_command **str_root)
{
	t_node_binary		*new_node;
	t_shell_separator	*sep;

	sep = ft_set_sep(line, j);
	if ((*root)->value == NULL)
	{
		(*root)->value = sep;
		(*root)->left = ft_binarytree_node_create(*str_root);
	}
	else
	{
		new_node = ft_binarytree_node_create(sep);
		(*root)->right = ft_binarytree_node_create(*str_root);
		new_node->left = *root;
		*root = new_node;
	}
	*str_root = ft_new_str_struct();
	if (sep->instruction_type == SHELL_SEPARATOR_TYPE_END
		|| sep->instruction_type == SHELL_SEPARATOR_TYPE_PIPE)
		return (j + 1);
	return (j + 2);
}

int	ft_is_separator(char *line, int j)
{
	if (line[j] == '&' && line[j + 1] == '&')
		return (1);
	else if (line[j] && (line[j] == ';' || line[j] == '|'))
		return (1);
	else
		return (0);
}

void	ft_fill_str_no_quotes(char *line, int j, int len, t_shell_command *str_struct)
{
	char	*s;
	int		k;

	k = 0;
	s = ft_managed_malloc(sizeof(char) * len + 1);
	s[len] = '\0';
	while (line[j] && line[j] != '\"' && line[j] != '\''
		&& ft_is_separator(line, j) == 0)
	{
		if (line[j] == '\\')
		{
			s[k] = line[j + 1];
			k++;
			j += 2;
		}
		else
		{
			s[k] = line[j];
			k++;
			j++;
		}
	}
	if (str_struct->command_string == NULL)
		str_struct->command_string = s;
	else
		str_struct->command_string = ft_strjoin_free(str_struct->command_string, s);
}


void	ft_fill_mask_no_quotes(char *line, char *mask, int j, t_shell_command *str_struct)
{
	int		k;

	k = 0;
	while (line[j] && line[j] != '\"' && line[j] != '\''
		&& ft_is_separator(line, j) == 0)
	{
		if (line[j] == '\\')
		{
			mask[k] = '1';
			k++;
			j += 2;
		}
		else
		{
			mask[k] = '0';
			k++;
			j++;
		}
	}
	if (str_struct->command_mask == NULL)
		str_struct->command_mask = mask;
	else
		str_struct->command_mask = ft_strjoin_free(str_struct->command_mask, mask);
}


int	ft_no_quote(char *line, int j, t_shell_command *str_struct)
{
	int		ret;
	int		backslash;
	char	*mask;

	ret = j;
	backslash = 0;
	while (line[ret] && line[ret] != '\"' && line[ret] != '\''
		&& ft_is_separator(line, ret) == 0)
	{
		if (line[ret] == '\\')
		{
			backslash++;
			ret++;
		}
		ret++;
	}
	mask = ft_managed_malloc(sizeof(char) * (ret - j + 1 - backslash));
	mask[ret - j - backslash] = '\0';
	ft_fill_mask_no_quotes(line, mask, j, str_struct);
	ft_fill_str_no_quotes(line, j, ret - j - backslash, str_struct);
	return (ret);
}

int	ft_show_tree(t_node_binary *root)
{
	char			node_type;
	t_node_binary	**buff;

	printf("\n\nSHOW TREE :\n\n");
	buff = &root;
	while (buff[0] != NULL)
	{
		node_type = *((char*)(buff[0]->value));
		printf("\nNodetype = %d\n", *((char*)(buff[0]->value)));
		if (*((char*)(buff[0]->value)) == 0)
			printf("\nNode str = %s\n", (((t_shell_command *)(buff[0]->value))->command_string));
		if (buff[0]->left != NULL)
		{
			printf("\nLeft_Nodetype = %d\n", *((char*)(buff[0]->left->value)));
			printf("\nRight_Nodetype = %d\n", *((char*)(buff[0]->right->value)));
			if (*((char*)(buff[0]->left->value)) == 0)
				printf("\nstr left = %s\n", (((t_shell_command *)(buff[0]->left->value))->command_string));
			if (*((char*)(buff[0]->right->value)) == 0)
				printf("\nstr right= %s\n", (((t_shell_command *)(buff[0]->right->value))->command_string));
			buff = &buff[0]->left;
		}
		else
			buff[0] = NULL;
	}
	return (0);
}

t_parse_struct	*ft_setup_parse_struct(void)
{
	t_parse_struct	*ret;

	ret = ft_managed_malloc(sizeof(t_parse_struct));
	ret->str_struct = ft_new_str_struct();
	ret->root = ft_managed_malloc(sizeof(t_node_binary *));
	ret->str_root = ft_managed_malloc(sizeof(t_shell_command *));
	ret->node = ft_binarytree_node_create(NULL);
	ret->str_root[0] = ret->str_struct;
	ret->root[0] = ret->node;
	return (ret);
}

t_node_binary	*ft_treat_line(char *line)
{
	int				i;
	int				j;
	t_parse_struct	*s;

	s = ft_setup_parse_struct();
	i = ft_strlen(line);
	j = 0;
	while (line[j])
	{
		if (ft_is_separator(line, j) == 1)
			j = ft_separator(line, s->root, j, s->str_root);
		if (line[j] != '\'' && line[j] != '\"')
			j = ft_no_quote(line, j, s->str_root[0]);
		else if (line[j] == '\'')
			j = ft_single_quote(line, j, s->str_root[0]);
		else if (line[j] == '\"')
			j = ft_double_quote(line, j, s->str_root[0]);
	}
	if ((s->root[0])->value == NULL)
		(s->root[0])->value = (s->str_root[0]);
	else if ((s->root[0])->right == NULL)
		(s->root[0])->right = ft_binarytree_node_create((s->str_root[0]));
	return (s->root[0]);
}

// int	main(void)
// {
// 	char			*line;
// 	char			*prompt;
// 	int				ret;
// 	t_node_binary	*root;

// 	ret = 0;
// 	prompt = ft_managed_malloc(sizeof(char) * 12);
// 	if (line == NULL || prompt == NULL)
// 		return (0);
// 	prompt = "\e[1;1H\e[2J";
// 	write(1, prompt, 11);
// 	prompt = "Minishell ~ ";
// 	while (ret >= 0)
// 	{
// 		write(1, prompt, 12);
// 		ret = get_next_line(0, &line);
// 		root = ft_treat_line(line);
// 		ft_show_tree(root);
// 		free(line);
// 	}
// 	return (1);
// }
