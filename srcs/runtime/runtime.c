/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:30:38 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/09 14:57:40 by fgalaup          ###   ########lyon.fr   */
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
		error_fatal(context, ERROR_RUNTIME_UNKNOWN_INSTRUCTION,
			1, (int)node_type);
	else
		return (run_separator(context, node_type, node));
	return (context->last_command_return_code);
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
	else if (node_type == SHELL_SEPARATOR_TYPE_AND)
		return (instruction_and(context, node));
	else if (node_type == SHELL_SEPARATOR_TYPE_OR)
		return (instruction_or(context, node));
	error_message(context, ERROR_SYNTAX_INVALID_INSTRUCTION, 1, node_type);
	return (1);
}
