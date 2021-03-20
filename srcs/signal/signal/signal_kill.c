/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_kill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felix <felix@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:17:01 by felix             #+#    #+#             */
/*   Updated: 2021/03/19 12:30:49 by felix            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_signal.h"

void	signal_kill(int signal)
{
	t_shell_context	*context;

	context = shell_get_context(NULL);
	if (context->running_command_pid != 0)
		kill(context->running_command_pid != 0, SIGQUIT);
	else
		context->last_command_return_code = 130;
}