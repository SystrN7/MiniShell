/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:41:47 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/14 16:47:16 by fgalaup          ###   ########lyon.fr   */
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
	int		pipe_fds[2];
	pid_t	pid;

	if (instruction_pipe_subshell(context) != 0)
		return (context->last_command_return_code);
	if (pipe((int *)&pipe_fds) == -1)
		error_fatal(context, ERROR_STD, 1);
	pid = fork();
	if (pid < 0)
		error_fatal(context, ERROR_STD, 1);
	else if (pid == 0)
		pipe_connect_side(context, node->left, pipe_fds, pipe_input);
	else
	{
		waitpid(pid, NULL, 0);
		pipe_connect_side(context, node->right, pipe_fds, pipe_output);
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

int	pipe_connect_side(
	t_shell_context *context,
	t_node_binary *node,
	int pipe_fds[],
	int pipe_side)
{
	int				pipe_use;
	int				pipe_unused;
	int				standard_use;

	pipe_use = pipe_side;
	if (pipe_side == pipe_input)
	{
		pipe_unused = pipe_output;
		standard_use = standard_output;
	}
	else
	{
		pipe_unused = pipe_input;
		standard_use = standard_input;
	}
	close(pipe_fds[pipe_unused]);
	if (dup2(pipe_fds[pipe_use], standard_use) == ERROR_STD)
		return (error_message(context, ERROR_STD, 1));
	run_instruction(context, node);
	close(pipe_fds[pipe_use]);
	exit(context->last_command_return_code);
}
