/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_new_prompt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 11:14:07 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/28 12:57:22 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_signal.h"

void	signal_new_prompt(int signal)
{
	t_shell_context	*context;

	(void) signal;
	context = shell_get_context(NULL);
	ft_putstr_fd(standard_output, "\n");
	if (context->commmand_running)
	{
		context->last_command_return_code = 130;
		return ;
	}
	context->last_command_return_code = 1;
	context->line_buff[0] = '\0';
	context->line_i = 0;
	console_prompt(context);
}
