/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 10:58:15 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/15 12:08:51 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_signal.h"

int	signal_register(t_shell_context *context)
{
	sig_t	status;

	// CTRL-C :
	status = signal(SIGINT, &signal_new_prompt);
	if (status == SIG_ERR)
		return (error_message(context, ERROR_STD, 1));
	// CTRL-\ :
	status = signal(SIGQUIT, &signal_do_nothing);
	if (status == SIG_ERR)
		return (error_message(context, ERROR_STD, 1));
	return (SUCCESS);
}
