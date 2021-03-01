/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:25:25 by fgalaup           #+#    #+#             */
/*   Updated: 2021/02/04 12:20:35 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell_command		*node_command_create(char *binary_path, char **argv)
{
	t_shell_command *node;

	node = ft_managed_malloc(sizeof(t_shell_command));
	if (node == NULL)
		return (NULL);
	node->instruction_type = SHELL_INSTRUCTION_COMMAND;
	node->path = binary_path;
	node->argv = argv;
	return (node);
}

void				node_command_delete(t_shell_command *node)
{
	ft_managed_free(node->path);
	ft_2d_free(node->path);
	node->instruction_type = SHELL_INSTRUCTION_UNKNOWN;
	node->path = NULL;
	node->argv = NULL;
	ft_managed_free(node);
}
