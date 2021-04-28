/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:47:01 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/28 12:51:43 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"
#include "minishell_builtin.h"
#include "minishell_utilities.h"
#include "minishell_parser.h"
#include "minishell_signal.h"

#include <unistd.h>

int	instruction_command(t_shell_context *context, t_node_binary *node)
{
	t_shell_command	*command;

	if (node->left != NULL)
		error_fatal(context, ERROR_SYNTAX_COMMAND_NOT_END, 1);
	if (node->right != NULL)
		error_fatal(context, ERROR_SYNTAX_COMMAND_NOT_END, 1);
	command = (t_shell_command *)node->value;
	if (command->command_string == NULL)
		return (context->last_command_return_code);
	instruction_command_prepare(context, command);
	if (command->argv[path] == NULL)
		return (context->last_command_return_code);
	context->last_command_return_code = 0;
	if (redirection_create(context, command->redirection))
		return (context->last_command_return_code);
	if (instruction_builtin_exec(context, command))
		instruction_command_exec(context, node->value);
	redirection_close(context, command->redirection);
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
	else if (!ft_strncmp(builtin->argv[path], BUILTIN_ENV, 4))
		return_code = builtin_env(context, argcount, builtin->argv);
	else if (!ft_strncmp(builtin->argv[path], BUILTIN_EXPORT, 7))
		return_code = builtin_export(context, argcount, builtin->argv);
	else if (!ft_strncmp(builtin->argv[path], BUILTIN_UNSET, 6))
		return_code = builtin_unset(context, argcount, builtin->argv);
	else if (!ft_strncmp(builtin->argv[path], BUILTIN_CD, 3))
		return_code = builtin_cd(context, argcount, builtin->argv);
	else if (!ft_strncmp(builtin->argv[path], BUILTIN_PWD, 4))
		return_code = builtin_pwd(context, argcount, builtin->argv);
	else if (!ft_strncmp(builtin->argv[path], BUILTIN_EXIT, 5))
		return_code = builtin_exit(context, argcount, builtin->argv);
	else
		return (FT_TRUE);
	context->last_command_return_code = return_code;
	return (FT_FALSE);
}

int	instruction_command_prepare(
	t_shell_context *context,
	t_shell_command *command
)
{
	ft_fix_argv(command);
	ft_treat_var(context, command);
	ft_managed_free(command->command_string);
	command->command_string = NULL;
	ft_managed_free(command->command_mask);
	command->command_mask = NULL;
	return (SUCCESS);
}

int	instruction_command_exec(t_shell_context *context, t_shell_command *command)
{
	pid_t	pid;
	int		status;

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
			env_destore_all(context->shared_environment));
		error_std(context, 127, command->path, NULL);
		if (errno == EACCES)
			context->last_command_return_code = 126;
		shell_shutdown(context);
	}
	else
		waitpid(pid, &status, 0);
	if (WTERMSIG(status) == SIGQUIT)
		write(standard_output, "Quit: 3\n", 8);
	return (context->last_command_return_code = WEXITSTATUS(status));
}

char	*command_path_resolver(
	t_shell_context *context,
	t_shell_command *command
)
{
	ft_managed_free(command->path);
	if (ft_strchr(command->argv[path], '/'))
		command->path = command->argv[path];
	else
		command->path = path_get_binary_path(
				env_get(context, "PATH"),
				command->argv[path]);
	if (command->path == NULL)
		error_message(
			context,
			ERROR_RUNTIME_UNKNOWN_COMMAND,
			127,
			command->argv[path]);
	return (command->path);
}
