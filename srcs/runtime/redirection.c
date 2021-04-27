/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:52:04 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/26 17:08:47 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"

/**
 *  >	REDIRECTION_OUTPUT 
 *  >>	REDIRECTION_APPEND_OUTPUT
 * 	<	REDIRECTION_INPUT
 **/

enum e_file
{
	REDIRECTION_OUTPUT = O_CREAT | O_WRONLY | O_TRUNC,
	REDIRECTION_APPEND_OUTPUT = O_CREAT | O_WRONLY | O_APPEND,
	REDIRECTION_INPUT = O_CREAT | O_RDONLY,
};

int	redirection_create(
	t_shell_context *context,
	t_redirection_list *redirections
)
{
	t_redirection_list	*it;

	it = redirections;
	while (it)
	{
		redirection_exec(context, it);
		it = it->next;
	}
	return (context->last_command_return_code);
}

int	redirection_exec(t_shell_context *context, t_redirection_list *redirection)
{
	int		fd;
	int		target_fd;

	fd = open(
			redirection->redirection_file,
			redirection_type_get_flag(redirection),
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == ERROR_STD)
		error_std(context, 1, redirection->redirection_file, NULL);
	else
	{
		if (redirection->source_fd <= -1)
			target_fd = standard_output;
		else if (redirection->source_fd <= 2)
			target_fd = redirection->source_fd;
		else if (redirection->redirection_type == SHELL_REDIRECT_TYPE_LEFT)
			target_fd = standard_input;
		else
			return (context->last_command_return_code);
		fd = dup2(fd, target_fd);
		if (fd == ERROR_STD)
			error_message(context, ERROR_STD, 1);
	}
	return (context->last_command_return_code);
}

int	redirection_close(
	t_shell_context *context,
	t_redirection_list *redirections
)
{
	if (redirections)
	{
		if (dup2(dup(context->standard_input_backup), standard_input) == -1)
			error_message(context, ERROR_STD, 1);
		if (dup2(dup(context->standard_output_backup), standard_output) == -1)
			error_message(context, ERROR_STD, 1);
		if (dup2(dup(context->standard_error_backup), standard_error) == -1)
			error_message(context, ERROR_STD, 1);
	}
	return (context->last_command_return_code);
}

int	redirection_type_get_flag(t_redirection_list *redirection)
{
	if (SHELL_REDIRECT_TYPE_LEFT == redirection->redirection_type)
		return (REDIRECTION_INPUT);
	else if (SHELL_REDIRECT_TYPE_RIGHT == redirection->redirection_type)
		return (REDIRECTION_OUTPUT);
	else if (SHELL_REDIRECT_TYPE_DOUBLE_RIGHT == redirection->redirection_type)
		return (REDIRECTION_APPEND_OUTPUT);
	return (0);
}
