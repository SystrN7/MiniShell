/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:41:47 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/18 11:45:55 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"

enum e_pipe
{
	pipe_input,
	pipe_output,
};

int	instruction_pipe(t_shell_context *context, t_node_binary *node)
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
		// printf("left progrma %s\n", ((t_shell_command *)node->left->value)->command_string);
		close(process_io[pipe_input]);
		if (dup2(process_io[pipe_output], standard_input) < 0)
			return (error_message(context, ERROR_STD, 1));
		close(process_io[pipe_input]);
		run_instruction(context, node->left);
		exit(context->last_command_return_code);
	}
	else
	{
		// printf("right progrma %s\n", ((t_shell_command *)node->right->value)->command_string);
		close(process_io[pipe_output]);
		if (dup2(process_io[pipe_input], standard_output) < 0)
			return (error_message(context, ERROR_STD, 1));
		close(process_io[pipe_output]);
		run_instruction(context, node->left);
	}
	return (context->last_command_return_code);
}

// int	instruction_pipe_subshell(t_shell_context *context, )
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid < 0)
// 		error_fatal(context, ERROR_STD, 1);
// 	if (pid != 0)
// 		waitpid(pid, &context->last_command_return_code, 0);
// 	return (pid);
// }

// int	instuction_pipe_connect(t_shell_context *context, )
// {
// 	close(process_io[pipe_output]);
// 	if (dup2(process_io[pipe_input], standard_output) < 0)
// 		return (error_message(context, ERROR_STD, 1));
// 	close(process_io[pipe_output]);

// 	return (SUCCESS);
// }
