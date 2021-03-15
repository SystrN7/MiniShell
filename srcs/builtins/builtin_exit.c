/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:28:33 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/15 10:17:11 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtin.h"

/**
 * Exit shell and return given status code.
 *  - Withous params is return last command status code
 *  - exit is write on stderr in error case
 *  - The arg need to be numeric status code 255
 * 	(bash: exit: 9995afds5: numeric argument required)
 *  - If more than one argument is given
 *    is cause error and shell dosent exit (bash: exit: too many arguments)
 **/

int	builtin_exit(t_shell_context *context, int argc, char **args)
{
	ft_printf_fd(standard_error, "exit\n");
	if (argc >= 2)
	{
		if (!ft_strtest(args[arg1], ft_isdigit))
			exit_error_invalid_argument(context, args[arg1]);
		else if (argc > 2)
			return (exit_error_too_many_argument(context));
		context->last_command_return_code = ft_atoi(args[arg1]);
	}
	shell_shutdown(context);
	return (0);
}

int	exit_error_invalid_argument(t_shell_context *context, const char *arg)
{
	ft_printf_fd(
		standard_error,
		"%s: exit: %s: numeric argument required\n",
		context->shell_name,
		arg
	);
	context->last_command_return_code = 255;
	shell_shutdown(context);
	return (context->last_command_return_code);
}

int	exit_error_too_many_argument(t_shell_context *context)
{
	ft_printf_fd(
		standard_error,
		"%s: exit: too many arguments\n",
		context->shell_name
	);
	context->last_command_return_code = 1;
	return (context->last_command_return_code);
}
