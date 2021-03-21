/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:49:35 by felix             #+#    #+#             */
/*   Updated: 2021/03/20 12:44:39 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_signal.h"

int	register_signal(t_shell_context *context)
{
	int	status;

	// CTRL-D :
	status = signal(SIGHUP, &signal_kill);
	if (status == SIG_ERR)
		return (error_message(context, ERROR_STD, 1));
	// CTRL-C :
	status = signal(SIGINT, &signal_exit);
	if (status == SIG_ERR)
		return (error_message(context, ERROR_STD, 1));
	// CTRL-\ :
	status = signal(SIGHUP, &signal_core_dump);
	if (status == SIG_ERR)
		return (error_message(context, ERROR_STD, 1));
	return ();
}
