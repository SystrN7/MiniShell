/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:39:17 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/11 15:22:15 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_error.h"

int	error_occure(char *error)
{
	ft_printf("%s\n", error);
	return (0);
}

int	error_fatal(
	t_shell_context *context,
	int error_code,
	int return_code,
	char *emitter
)
{
	error_message(context, error_code, return_code, emitter);
	shell_shutdown(context);
	return (return_code);
}

int	error_message(
	t_shell_context *context,
	int error_code,
	int return_code,
	char *emitter
)
{
	char	*error_message;

	error_message = error_get_message(error_code);
	if (emitter)
		ft_printf_fd(
			standard_error,
			"%s: %s: %s\n",
			context->shell_name,
			emitter,
			error_message
		);
	else
		ft_printf_fd(
			standard_error,
			"%s: %s\n",
			context->shell_name,
			error_message
		);
	context->last_command_return_code = return_code;
	return (return_code);
}

int	error_new(
	t_shell_context *context,
	int error_code,
	int return_code,
	...
)
{
	va_list	args;
	char	*buffer;
	int		size;
	char	*error_message;

	buffer = NULL;
	error_message = error_get_message(error_code);
	va_start(args, return_code);
	size = ft_format(error_message, args, &buffer);
	va_end(args);
	write(2, buffer, size);
	ft_printf_fd(standard_error, "%s: ", context->shell_name);
	ft_managed_free(buffer);
	context->last_command_return_code = return_code;
	return (return_code);
}

char	*error_get_message(int	error_code)
{
	size_t	i;

	if (error_code == ERROR_STD)
		return (strerror(errno));
	i = 0;
	while (error_messages[i].code != 0 && error_messages[i].message != NULL)
		if (error_messages[i++].code == error_code)
			return (error_messages[i].message);
	return (NULL);
}
