/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:18:34 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/14 11:03:07 by seruiz           ###   ########lyon.fr   */
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
	t_node_binary	*it;

	it = root;

	if (*((char *)(root->value)) == SHELL_INSTRUCTION_COMMAND)
		ft_catch_redirection_before((t_shell_command *)(root->value));
	while (it)
	{
		if (it->left != NULL && it->left->value != NULL
			&& get_node_type(it->left) == SHELL_INSTRUCTION_COMMAND)
			ft_catch_redirection_before((t_shell_command *)(it->left->value));
		if (it->right != NULL && it->right->value != NULL
			&& get_node_type(it->right) == SHELL_INSTRUCTION_COMMAND)
			ft_catch_redirection_before((t_shell_command *)(it->right->value));
		it = it->left;
	}
	return (0);
}

t_parse_struct	*ft_setup_parse_struct(void)
{
	t_parse_struct	*ret;

	ret = ft_managed_malloc(sizeof(t_parse_struct));
	//ret->str_struct = ft_new_str_struct();
	ret->str_struct = NULL;
	ret->root = ft_managed_malloc(sizeof(t_node_binary *));
	//ret->root = NULL;
	ret->str_root = ft_managed_malloc(sizeof(t_shell_command *));
	//ret->str_root = NULL;
	ret->node = ft_binarytree_node_create(NULL);
	ret->node->left = NULL;
	ret->node->right = NULL;
	//ret->node = NULL;
	//ret->str_root[0] = ret->str_struct;
	*(ret->root) = ret->node;
	return (ret);
}

int	ft_node_exists(char *line, int j, t_shell_command **str_root)
{
	if (line[j] != '\'' && line[j] != '\"')
		j = ft_no_quote(line, j, *str_root);
	else if (line[j] == '\'')
		j = ft_single_quote(line, j, *str_root);
	else if (line[j] == '\"')
		j = ft_double_quote(line, j, *str_root);
	return (j);
}

t_node_binary	*ft_new_command(void)
{
	t_node_binary	*new_node;
	t_shell_command	*new_command;

	new_command = ft_managed_malloc(sizeof(t_shell_command));
	new_command->instruction_type = SHELL_INSTRUCTION_COMMAND;
	new_command->argv = NULL;
	new_command->command_mask = NULL;
	new_command->command_string = NULL;
	new_command->masks = NULL;
	new_command->path = NULL;
	new_command->redirection = NULL;
	new_node = ft_binarytree_node_create(new_command);
	return (new_node);
}

int	ft_first_command(char *line, int j, t_node_binary **root)
{
	if (line[j] != '\'' && line[j] != '\"')
		j = ft_no_quote(line, j, (*root)->value);
	else if (line[j] == '\'')
		j = ft_single_quote(line, j, (*root)->value);
	else if (line[j] == '\"')
		j = ft_double_quote(line, j, (*root)->value);
	return (j);
}


int	ft_is_cmd(char *line, int j, t_node_binary **root, t_shell_command **str_root, int sep_found)
{
	t_node_binary *new_node;

	if ((*root)->value == NULL)
	{
		(*str_root) = ft_new_str_struct();
		(*root)->value = *str_root;
		return (ft_first_command(line, j, root));
	}
	else if ((*root)->left == NULL && sep_found == 1)
	{
		(*str_root) = ft_new_str_struct();
		new_node = ft_binarytree_node_create((*str_root));
		(*root)->left = new_node;
	}
	else if ((*root)->right == NULL && sep_found == 1)
	{
		(*str_root) = ft_new_str_struct();
		new_node = ft_binarytree_node_create(*str_root);
		(*root)->right = new_node;
	}
	else
		return (ft_node_exists(line, j, str_root));
	if (line[j] != '\'' && line[j] != '\"')
		j = ft_no_quote(line, j, new_node->value);
	else if (line[j] == '\'')
		j = ft_single_quote(line, j, new_node->value);
	else if (line[j] == '\"')
		j = ft_double_quote(line, j, new_node->value);
	return (j);
}

t_node_binary	*ft_treat_line(char *line)
{
	int				j;
	int				sep_found;
	t_parse_struct	*s;

	s = ft_setup_parse_struct();
	j = 0;
	while (line[j])
	{
		if (ft_is_separator(line, j) == 1)
		{
			j = ft_separator(line, s->root, j, s->str_root);
			sep_found = 1;
		}
		else
		{
			j = ft_is_cmd(line, j, s->root, s->str_root, sep_found);
			sep_found = 0;
		}
	}
	if (j == 0)
		return (NULL);
	//if ((*s->root)->value == NULL)
	//	(*s->root)->value = (*s->str_root);
	//else if ((*s->root)->right == NULL)
	//	(*s->root)->right = ft_binarytree_node_create(*(s->str_root));
	ft_set_redirection(*(s->root));
	return (*s->root);
}
