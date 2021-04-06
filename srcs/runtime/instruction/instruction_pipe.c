/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:41:47 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/06 16:54:21 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"

enum e_pipe
{
	pipe_output,
	pipe_input,
};

int	instruction_pipe(t_shell_context *context, t_node_binary *node)
{
	int		process_io[2];
	pid_t	pid;

	if (instruction_pipe_subshell(context) != 0)
		return (context->last_command_return_code);
	if (pipe((int *)&process_io) == -1)
		error_fatal(context, ERROR_STD, 1);
	pid = fork();
	if (pid < 0)
		error_fatal(context, ERROR_STD, 1);
	else if (pid == 0)
	{
		// child (standard output)->(pipe input);
		close(process_io[pipe_output]);
		if (dup2(process_io[pipe_input], standard_output) < 0)
			return (error_message(context, ERROR_STD, 1));
		run_instruction(context, node->left);
		close(process_io[pipe_output]);
		exit(context->last_command_return_code);
	}
	else
	{
		// parent (pipe output)->(standard input);
		close(process_io[pipe_input]);
		if (dup2(process_io[pipe_output], standard_input) < 0)
			return (error_message(context, ERROR_STD, 1));
		run_instruction(context, node->right);
		close(process_io[pipe_input]);
		exit(context->last_command_return_code % 256);
	}
	return (context->last_command_return_code);
}

int	instruction_pipe_subshell(t_shell_context *context)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		error_fatal(context, ERROR_STD, 1);
	if (pid != 0)
		waitpid(pid, &status, 0);
	context->last_command_return_code = WEXITSTATUS(status);
	return (pid);
}

// int pipe_connect()

// int	instuction_pipe_connect(t_shell_context *context, in)
// {
// 	close(process_io[pipe_input]);
// 	if (dup2(process_io[pipe_output], standard_output) < 0)
// 		return (error_message(context, ERROR_STD, 1));
// 	close(process_io[pipe_input]);

// 	return (SUCCESS);
// }
