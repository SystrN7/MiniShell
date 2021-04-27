/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:28:33 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/26 16:33:50 by fgalaup          ###   ########lyon.fr   */
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
	if (context->interactive_mode)
		ft_printf_fd(standard_error, "exit\n");
	if (argc >= 2)
	{
		if (args[arg1][0] == '\0' || !ft_strtest(args[arg1], ft_isdigit))
		{
			error_builtin(context,
				ERROR_ARG_REQUIRE_NUMERIC, 255,
				args[path], NULL, args[1]);
			shell_shutdown(context);
		}
		else if (argc > 2)
			return (error_builtin(
					context,
					ERROR_ARG_TOO_MANY, 1,
					args[path], NULL)
			);
		context->last_command_return_code = ft_atoi(args[arg1]);
	}
	shell_shutdown(context);
	return (context->last_command_return_code);
}
