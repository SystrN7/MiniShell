/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:00:30 by fgalaup           #+#    #+#             */
/*   Updated: 2021/02/08 15:35:53 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtin.h"

int		builtin_echo(t_shell_context *context, int argv, char **args)
{
	int		i;
	t_bool	option_n;

	if (ft_strncmp("-n", args[0], 2))
		option_n = TRUE;
	else
		option_n = FALSE;
	i = option_n;
	while (args[i])
	{
		ft_putstr_fd(1, args[i]);
		if (args[i++])
			write(1, " ", 1);
	}
	if (option_n)
		write(1, "\n", 1);
	return (0);
}
