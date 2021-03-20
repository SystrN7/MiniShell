/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felix <felix@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:52:04 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/19 10:14:03 by felix            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"

enum e_file
{
	REDIRECTION_INPUT = O_CREAT | O_RDONLY,
	REDIRECTION_OUTPUT = O_CREAT | O_WRONLY,
	REDIRECTION_APPEND_OUTPUT = O_CREAT | O_APPEND | O_WRONLY,
};

int	redirection_create(t_shell_context *context, t_list *redirections)
{
	t_list	*it;

	it = redirections;
	while (it)
	{
		printf("%p-%p-%p\n",context, it, it->content);
		redirection_exec(context, it->content);
		it = it->next;
	}
	return (SUCCESS);
}

int	redirection_exec(t_shell_context *context, t_shell_redirection *redirection)
{
	int		fd;
	int		target_fd;

	fd = open(redirection->file_name, redirection_type_get_flag(redirection));
	if (fd == ERROR_STD)
		error_message(context, ERROR_STD, 1);
	else
	{
		target_fd = standard_output;
		if ((redirection->type == SHELL_REDIRECT_TYPE_RIGHT)
			&& (redirection->type == SHELL_REDIRECT_TYPE_DOUBLE_RIGHT))
			target_fd = standard_input;
		fd = dup2(fd, target_fd);
		if (fd == ERROR_STD)
			error_message(context, ERROR_STD, 1);
	}
	return (context->last_command_return_code);
}

int	redirection_close(t_shell_context *context, t_list *redirections)
{
	t_shell_redirection	*redirection;
	t_list				*it;

	if (dup2(context->standard_input_backup, standard_input))
		error_message(context, ERROR_STD, 1);
	if (dup2(context->standard_output_backup, standard_output))
		error_message(context, ERROR_STD, 1);
	it = redirections;
	while (it)
	{
		redirection = it->content;
		if (close(redirection->fd) == ERROR_STD)
			error_message(context, ERROR_STD, 1);
		it = it->next;
	}
	return (SUCCESS);
}

int	redirection_type_get_flag(t_shell_redirection *redirection)
{
	if (SHELL_REDIRECT_TYPE_LEFT == redirection->type)
		return (REDIRECTION_INPUT);
	else if (SHELL_REDIRECT_TYPE_RIGHT == redirection->type)
		return (REDIRECTION_OUTPUT);
	else if (SHELL_REDIRECT_TYPE_DOUBLE_RIGHT == redirection->type)
		return (REDIRECTION_APPEND_OUTPUT);
	return (0);
}
