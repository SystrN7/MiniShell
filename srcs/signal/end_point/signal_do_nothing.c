/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_do_nothing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 11:06:57 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/28 12:38:29 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_signal.h"

void	signal_do_nothing(int signal)
{
	t_shell_context	*context;

	(void) signal;
	context = shell_get_context(NULL);
	if (context->commmand_running)
	{
		write(standard_output, "Quit: 3\n", 8);
		context->last_command_return_code = 131;
	}
}
