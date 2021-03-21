/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_core_dump.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:05:49 by felix             #+#    #+#             */
/*   Updated: 2021/03/21 11:26:06 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_signal.h"

void signal_core_dump(int signal)
{
	t_shell_context *context;


	context = get_context(NULL);
	if (context->running_command_pid != 0)
		kill(context->running_command_pid != 0, SIGQUIT);
}
