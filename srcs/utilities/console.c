/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 11:21:21 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/23 10:58:06 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utilities.h"
#include "sys/syslimits.h"

void	console_clear(void)
{
	ft_putstr_fd(standard_output, "\e[1;1H\e[2J");
}

int	console_prompt(t_shell_context *context)
{
	char	path_buffer[PATH_MAX];
	int		len;

	getcwd(path_buffer, PATH_MAX);
	len = ft_printf("%s-[%s]-(%d)-$ ", context->shell_name, path_buffer,
			context->last_command_return_code);
	return (len);
}
