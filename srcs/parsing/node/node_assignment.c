/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_assignment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:13:48 by fgalaup           #+#    #+#             */
/*   Updated: 2021/02/08 11:24:34 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell_command		*node_assignment_create(char *key, char *value)
{
	t_shell_assignment *node;

	node = ft_managed_malloc(sizeof(t_shell_assignment));
	if (node == NULL)
		return (NULL);
	node->instruction_type = SHELL_INSTRUCTION_ASSIGN;
	node->key = key;
	node->value = value;
	return (node);
}

void				node_assignment_delete(t_shell_assignment *node)
{
	ft_managed_free(node->path);
	ft_2d_free(node->path);
	node->instruction_type = SHELL_INSTRUCTION_UNKNOWN;
	node->path = NULL;
	node->argv = NULL;
	ft_managed_free(node);
}
