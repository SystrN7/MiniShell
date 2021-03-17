/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 11:21:21 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/17 12:46:11 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utilities.h"
#include "sys/syslimits.h"

void	console_clear(void)
{
	ft_putstr_fd(standard_output, "\e[1;1H\e[2J");
}

void	console_prompt(t_shell_context *context)
{
	char	path_buffer[PATH_MAX];

	getcwd(path_buffer, PATH_MAX);
	ft_putstr_fd(standard_output, context->shell_name);
	ft_putstr_fd(standard_output, "-[");
	ft_putstr_fd(standard_output, path_buffer);
	ft_putstr_fd(standard_output, "]-(");
	ft_putnbr_fd(standard_output, context->last_command_return_code);
	ft_putstr_fd(standard_output, ")-$ ");
}
