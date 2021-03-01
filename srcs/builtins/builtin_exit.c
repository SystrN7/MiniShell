/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:28:33 by fgalaup           #+#    #+#             */
/*   Updated: 2021/02/08 16:35:45 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtin.h"

/*
** Exit shell and return given status code.
**  - Withous params is return last command status code
**  - exit is write on stderr in error case
**  - The arg need to be numeric status code 2
** 	(bash: exit: 9995afds5: numeric argument required)
**  - If more than one argument is given
**    is cause error and shell dosent exit (bash: exit: too many arguments)
*/

int		builtin_exit(t_shell_context *context, int argv, char **args)
{
	int return_code;

	return_code = 0;
	if (ft_2d_count(args) <= 2)
	{
		if (ft_isdigit)
			return_code = ft_atoi(args[1]);
		else
			return_code = 2;
		context->last_command_return_code = return_code;
		shell_shutdown(context);
	}
	return (1);
}
