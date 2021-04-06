/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:18:34 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/06 15:49:45 by seruiz           ###   ########lyon.fr   */
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

int	ft_set_redirection(t_node_binary *root)
{
	char			node_type;
	t_node_binary	**buff;

	buff = &root;
	while (buff[0] != NULL)
	{
		node_type = *((char*)(buff[0]->value));
		if (*((char*)(buff[0]->value)) == SHELL_INSTRUCTION_COMMAND)
			ft_catch_redirection_before((t_shell_command *)(buff[0]->value));
		if (buff[0]->left != NULL)
		{
			if (*((char*)(buff[0]->left->value)) == SHELL_INSTRUCTION_COMMAND)
				ft_catch_redirection_before((t_shell_command *)(buff[0]->left->value));
			if (*((char*)(buff[0]->right->value)) == SHELL_INSTRUCTION_COMMAND)
				ft_catch_redirection_before((t_shell_command *)(buff[0]->right->value));
			buff = &buff[0]->left;
		}
		else
			buff[0] = NULL;
	}
	return (0);
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
		if (*((char*)(buff[0]->value)) == SHELL_INSTRUCTION_COMMAND)
			printf("\nNode str = %s\n", (((t_shell_command *)(buff[0]->value))->command_string));
		if (buff[0]->left != NULL)
		{
			printf("\nLeft_Nodetype = %d\n", *((char*)(buff[0]->left->value)));
			printf("\nRight_Nodetype = %d\n", *((char*)(buff[0]->right->value)));
			if (*((char*)(buff[0]->left->value)) == SHELL_INSTRUCTION_COMMAND)
				printf("\nstr left = %s\n", (((t_shell_command *)(buff[0]->left->value))->command_string));
			if (*((char*)(buff[0]->right->value)) == SHELL_INSTRUCTION_COMMAND)
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
	//else if ((s->root[0])->right == NULL)
	//	(s->root[0])->right = ft_binarytree_node_create((s->str_root[0]));
	ft_set_redirection(*s->root);
	return (s->root[0]);
}
