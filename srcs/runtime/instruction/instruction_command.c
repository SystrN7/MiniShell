/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:47:01 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/12 16:46:55 by fgalaup          ###   ########lyon.fr   */
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
		error_fatal(context, ERROR_SYNTAX_COMMAND_NOT_END, 1);
	if (node->right != NULL)
		error_fatal(context, ERROR_SYNTAX_COMMAND_NOT_END, 1);
	command = (t_shell_command*)node->value;
	context->last_command_return_code = 0;
	instruction_command_prepare(context, command);
	if (instruction_builtin_exec(context, command))
		instruction_command_exec(context, node->value);
	return (context->last_command_return_code);
}

int	instruction_builtin_exec(t_shell_context *context, t_shell_command *builtin)
{
	int		return_code;
	int		argcount;

	return_code = 0;
	builtin->path = ft_strdup(builtin->argv[path]);
	ft_striter(builtin->path, ft_tolower);
	argcount = ft_2d_count((void **)builtin->argv);
	if (!ft_strncmp(builtin->path, BUILTIN_ECHO, 5))
		return_code = builtin_echo(context, argcount, builtin->argv);
	else if (!ft_strncmp(builtin->path, BUILTIN_ENV, 4))
		return_code = builtin_env(context, argcount, builtin->argv);
	else if (!ft_strncmp(builtin->path, BUILTIN_EXPORT, 7))
		return_code = builtin_export(context, argcount, builtin->argv);
	else if (!ft_strncmp(builtin->path, BUILTIN_UNSET, 6))
		return_code = builtin_unset(context, argcount, builtin->argv);
	else if (!ft_strncmp(builtin->path, BUILTIN_CD, 3))
		return_code = builtin_cd(context, argcount, builtin->argv);
	else if (!ft_strncmp(builtin->path, BUILTIN_PWD, 4))
		return_code = builtin_pwd(context, argcount, builtin->argv);
	else if (!ft_strncmp(builtin->path, BUILTIN_EXIT, 5))
		return_code = builtin_exit(context, argcount, builtin->argv);
	else
		return (TRUE);
	context->last_command_return_code = return_code;
	return (FALSE);
}

int instruction_command_prepare(t_shell_context *context, t_shell_command *command)
{
	(void)context;
	command->argv = ft_split(command->command_string, ' ');
	ft_managed_free(command->command_string);
	command->command_string = NULL;
	ft_managed_free(command->command_mask);
	command->command_mask = NULL;
	return (SUCCESS);
}

int	instruction_command_exec(t_shell_context *context, t_shell_command *command)
{
	pid_t	pid;

	command_path_resolver(context, command);
	if (command->path == NULL)
		return (context->last_command_return_code);
	pid = fork();
	if (pid == -1)
		error_fatal(context, ERROR_STD, 1);
	else if (pid == 0)
	{
		execve(
			command->path,
			command->argv,
			env_destore_all(context->shared_environment)
		);
		error_fatal(context, ERROR_STD, 1);
	}
	else
		waitpid(pid, &context->last_command_return_code, 0);
	return (context->last_command_return_code);
}

char	*command_path_resolver(t_shell_context *context, t_shell_command *command)
{
	ft_managed_free(command->path);
	command->path = path_get_binary_path(
			env_get(context, "PATH"),
			command->argv[path]
		);
	if (!command->path)
		error_message(
			context,
			ERROR_RUNTIME_UNKNOWN_COMMAND,
			127,
			command->argv[path]
		);
	return (command->path);
}
