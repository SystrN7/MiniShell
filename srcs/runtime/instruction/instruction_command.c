/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:47:01 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/11 15:04:37 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"
#include "minishell_builtin.h"
#include "minishell_utilities.h"

#include <unistd.h>

int	instruction_command(t_shell_context *context, t_node_binary *node)
{
	t_shell_command	*command;

	if (node->left != NULL)
		error_occure("builtin is not end node");
	if (node->right != NULL)
		error_occure("builtin is not end node");
	command = (t_shell_command*)node->value;
	// ft_striter(command->argv, ft_tolower);
	context->last_command_return_code = 0;
	if (instruction_builtin_exec(context, command))
		instruction_command_exec(context, node->value);
	return (context->last_command_return_code);
}

int	instruction_builtin_exec(t_shell_context *context, t_shell_command *builtin)
{
	int		return_code;
	int		argcount;

	return_code = 0;
	argcount = ft_2d_count((void **)builtin->argv);
	if (!ft_strncmp(builtin->argv[path], BUILTIN_ECHO, 5))
		return_code = builtin_echo(context, argcount, builtin->argv);
	else if (ft_strncmp(builtin->argv[path], BUILTIN_ENV, 4))
		return_code = builtin_env(context, argcount, builtin->argv);
	else if (ft_strncmp(builtin->argv[path], BUILTIN_EXPORT, 7))
		return_code = builtin_export(context, argcount, builtin->argv);
	else if (ft_strncmp(builtin->argv[path], BUILTIN_UNSET, 6))
		return_code = builtin_unset(context, argcount, builtin->argv);
	else if (ft_strncmp(builtin->argv[path], BUILTIN_CD, 3))
		return_code = builtin_cd(context, argcount, builtin->argv);
	else if (ft_strncmp(builtin->argv[path], BUILTIN_PWD, 4))
		return_code = builtin_pwd(context, argcount, builtin->argv);
	else if (ft_strncmp(builtin->argv[path], BUILTIN_EXIT, 5))
		return_code = builtin_exit(context, argcount, builtin->argv);
	else
		return (FALSE);
	context->last_command_return_code = return_code;
	return (TRUE);
}

int	instruction_command_exec(t_shell_context *context, t_shell_command *command)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_occure("error durring fork");
	else if (pid == 0)
	{
		execve(
			command_path_resolver(context, command),
			command->argv,
			env_destore_all(context->shared_environment)
		);
		error_occure("execve fail please checks errno");
	}
	else
		waitpid(pid, &context->last_command_return_code, 0);
	return (context->last_command_return_code);
}

char	*command_path_resolver(t_shell_context *context, t_shell_command *command)
{
	char	*binary_path;

	binary_path = path_get_binary_path(
			env_get(context, "PATH"),
			command->argv[path]
		);
	ft_managed_free(command->argv[path]);
	command->path = binary_path;
	return (binary_path);
}
