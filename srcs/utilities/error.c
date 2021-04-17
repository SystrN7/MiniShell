/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:39:17 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/17 15:57:30 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_error.h"

int	error_fatal(
	t_shell_context *context,
	int error_code,
	int return_code,
	 ...
)
{
	va_list	args;

	ft_printf_fd(standard_error, "%s: ", context->shell_name);
	if (!context->interactive_mode)
		ft_printf_fd(standard_error, "line %d: ", context->line_number);
	va_start(args, return_code);
	error_print_messages(context, error_code, return_code, args);
	va_end(args);
	shell_shutdown(context);
	return (return_code);
}

int	error_message(
	t_shell_context *context,
	int error_code,
	int return_code,
	 ...
)
{
	va_list	args;

	ft_printf_fd(standard_error, "%s: ", context->shell_name);
	if (!context->interactive_mode)
		ft_printf_fd(standard_error, "line %d: ", context->line_number);
	va_start(args, return_code);
	error_print_messages(context, error_code, return_code, args);
	va_end(args);
	return (return_code);
}

int	error_std(
	t_shell_context *context,
	int return_code,
	 ...
)
{
	va_list	args;

	ft_printf_fd(standard_error, "%s: ", context->shell_name);
	if (!context->interactive_mode)
		ft_printf_fd(standard_error, "line %d: ", context->line_number);
	va_start(args, return_code);
	error_print_origin(args);
	error_print_messages(context, ERROR_STD, return_code, args);
	va_end(args);
	return (return_code);
}

int	error_builtin(
	t_shell_context *context,
	int error_code,
	int return_code,
	 ...
)
{
	va_list	args;

	ft_printf_fd(standard_error, "%s: ", context->shell_name);
	if (!context->interactive_mode)
		ft_printf_fd(standard_error, "line %d: ", context->line_number);
	va_start(args, return_code);
	error_print_origin(args);
	error_print_messages(context, error_code, return_code, args);
	va_end(args);
	return (return_code);
}
