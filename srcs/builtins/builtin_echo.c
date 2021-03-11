/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:00:30 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/10 14:45:13 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtin.h"

int	builtin_echo(t_shell_context *context, int argc, char **args)
{
	int		i;
	t_bool	option_n;

	if (argc > 1)
		option_n = builtin_echo_option_n(args);
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

int	builtin_echo_option_n(char **args)
{
	int		i;
	t_bool	option_n;

	i = 0;
	option_n = 0;
	if (args[1][i] == '-')
	{
		while (args[1][i])
		{
			if (args[1][i++] == 'n')
				option_n = TRUE;
			else
			{
				option_n = FALSE;
				break ;
			}
		}
	}
	return (option_n);
}
