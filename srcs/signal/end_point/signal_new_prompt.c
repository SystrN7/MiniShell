/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_new_prompt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 11:14:07 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/21 12:32:28 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_signal.h"

void	signal_new_prompt(int signal)
{
	t_shell_context	*context;

	(void) signal;
	context = shell_get_context(NULL);
	context->last_command_return_code = 1;
	ft_putstr_fd(standard_output, "\b\b  \n");
	console_prompt(context);
}
