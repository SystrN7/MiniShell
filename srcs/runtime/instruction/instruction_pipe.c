/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:41:47 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/12 10:10:27 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"

int		instruction_pipe(t_shell_context *context, t_node_binary *node)
{
	int		process_io[2];
	pid_t	pid;

	if (pipe((int *)&process_io) == -1)
		error_fatal(context, ERROR_STD, 1);
	pid = fork();
	if (pid < 0)
		error_fatal(context, ERROR_STD, 1);
	else if (pid == 0)
	{
		dup2(process_io[1], standard_output);
		run_instruction(context, node->left);
		exit(context->last_command_return_code);
	}
	else
	{
		run_instruction(context, node->right);
		waitpid(pid, &context->last_command_return_code, 0);
	}
	return (context->last_command_return_code);
}
