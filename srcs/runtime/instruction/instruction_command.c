/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:47:01 by fgalaup           #+#    #+#             */
/*   Updated: 2021/02/20 14:43:07 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"
#include "minishell_utilities.h"

#include <unistd.h>

int		instruction_command(t_shell_context *context, t_node_binary *node)
{
	t_shell_command	*command;
	char			*path;
	char			*env_path;

	if (node->left != NULL)
		error_occure("builtin is not end node");
	if (node->right != NULL)
		error_occure("builtin is not end node");
	command = (t_shell_command*)node->value;
	env_path = env_get(context, "PATH");
	path = path_get_binary_path(env_path, command->path);
	ft_managed_free(command->path);
	command->path = path;
	command_run(context, node->value);
	return (context->last_command_return_code);
}

// int		command_path_resolver()
// {
// 	return 
// }

int		command_run(t_shell_context *context, t_shell_command *command)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_occurs("error durring fork");
	else if (pid == 0)
	{
		execve(
			command->path,
			command->argv,
			env_destore_all(context->shared_environment)
		);
		error_occurs("execve fail please checks errno");
	}
	else
		waitpid(pid, &context->last_command_return_code, 0);
	return (context->last_command_return_code);
}
