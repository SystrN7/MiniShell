/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:18:34 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/28 12:52:13 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parser.h"

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

int	ft_node_exists(char *line, int j, t_shell_command **str_root)
{
	if (line[j] != '\'' && line[j] != '\"')
		j = ft_no_quote(line, j, *str_root);
	else if (line[j] == '\'')
		j = ft_single_quote(line, j, *str_root);
	else if (line[j] == '\"')
		j = ft_double_quote(line, j, *str_root, 0);
	return (j);
}

int	ft_first_command(char *line, int j, t_node_binary **root)
{
	if (line[j] != '\'' && line[j] != '\"')
		j = ft_no_quote(line, j, (*root)->value);
	else if (line[j] == '\'')
		j = ft_single_quote(line, j, (*root)->value);
	else if (line[j] == '\"')
		j = ft_double_quote(line, j, (*root)->value, 0);
	return (j);
}

int	ft_is_cmd(
	char *line,
	t_node_binary **root,
	t_shell_command **str_root,
	t_parser_ints i
)
{
	t_node_binary	*new_node;

	if ((*root)->value == NULL)
		return (ft_root_val_null(root, str_root, line, i.j));
	else if ((*root)->left == 0 && i.sep_found == 1 && (*root)->right != NULL)
	{
		(*str_root) = ft_new_str_struct();
		new_node = ft_binarytree_node_create((*str_root));
		(*root)->left = new_node;
	}
	else if ((*root)->right == NULL && i.sep_found == 1)
	{
		(*str_root) = ft_new_str_struct();
		new_node = ft_binarytree_node_create(*str_root);
		(*root)->right = new_node;
	}
	else
		return (ft_node_exists(line, i.j, str_root));
	if (line[i.j] != '\'' && line[i.j] != '\"')
		i.j = ft_no_quote(line, i.j, new_node->value);
	else if (line[i.j] == '\'')
		i.j = ft_single_quote(line, i.j, new_node->value);
	else if (line[i.j] == '\"')
		i.j = ft_double_quote(line, i.j, new_node->value, 0);
	return (i.j);
}

t_node_binary	*ft_treat_line(char *line)
{
	t_parse_struct	s;
	t_parser_ints	i;

	ft_setup_parse_struct(&s);
	i.j = 0;
	while (line[i.j])
	{
		if (ft_is_separator(line, i.j) == 1)
		{
			i.j = ft_separator(line, &s.root, i.j, &s.str_root);
			i.sep_found = FT_TRUE;
		}
		else if (line[i.j] == ' ' && i.sep_found == 1)
			i.j++;
		else
		{
			i.j = ft_is_cmd(line, &s.root, &s.str_root, i);
			i.sep_found = FT_FALSE;
		}
	}
	if (i.j == 0)
		return (NULL);
	ft_set_redirection(s.root);
	return (s.root);
}
