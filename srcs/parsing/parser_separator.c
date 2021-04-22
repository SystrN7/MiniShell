/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_separator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:23:16 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/22 17:01:53 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parser.h"

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

int	ft_separator(char *line, t_node_binary **root, int j,
		t_shell_command **str_root)
{
	t_node_binary		*new_node;
	t_shell_separator	*sep;

	(void)str_root;
	sep = ft_set_sep(line, j);
	if ((*root)->value == NULL)
		(*root)->value = sep;
	else
	{
		new_node = ft_binarytree_node_create(sep);
		new_node->left = *root;
		*root = new_node;
	}
	if (sep->instruction_type == SHELL_SEPARATOR_TYPE_END
		|| sep->instruction_type == SHELL_SEPARATOR_TYPE_PIPE)
		return (j + 1);
	return (j + 2);
}

int	ft_is_separator(char *line, int j)
{
	if (line[j] == '&' && line[j + 1] && line[j + 1] == '&')
		return (1);
	else if (line[j] && (line[j] == ';' || line[j] == '|'))
		return (1);
	else
		return (0);
}
