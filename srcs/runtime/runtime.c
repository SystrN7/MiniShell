/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:30:38 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/11 11:01:46 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"

int	run_instruction(t_shell_context *context, t_node_binary *node)
{
	char	node_type;

	node_type = *((char *)(node->value));
	if (node_type == SHELL_INSTRUCTION_COMMAND)
		return (instruction_command(context, node));
	else if (node_type == SHELL_INSTRUCTION_UNKNOWN)
		return (404);
	else
		return (run_separator(context, node_type, node));
	return (SUCCESS);
}

int	run_separator(
	t_shell_context *context,
	char node_type,
	t_node_binary *node
)
{
	if (node_type == SHELL_SEPARATOR_TYPE_END)
		return (instruction_separator(context, node));
	else if (node_type == SHELL_SEPARATOR_TYPE_PIPE)
		return (instruction_pipe(context, node));
	else if (node_type == SHELL_SEPARATOR_AND)
		return (instruction_and(context, node));
	else if (node_type == SHELL_SEPARATOR_OR)
		return (instruction_or(context, node));
	error_message("separator not found");
	return (1);
}
