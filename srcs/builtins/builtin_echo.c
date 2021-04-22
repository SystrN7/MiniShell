/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:00:30 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/22 17:32:59 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtin.h"

int	builtin_echo(t_shell_context *context, int argc, char **args)
{
	int		i;
	t_bool	option_n;

	(void)context;
	option_n = FT_FALSE;
	if (argc > 1)
		option_n = builtin_echo_option_n(args);
	i = option_n + 1;
	while (args[i])
	{
		ft_putstr_fd(1, args[i]);
		if (args[++i])
			write(1, " ", 1);
	}
	if (!option_n)
		write(1, "\n", 1);
	return (0);
}

int	builtin_echo_option_n(char *args[])
{
	size_t	i;
	size_t	j;
	int		option_n;

	i = 1;
	option_n = 0;
	while (args[i])
	{
		j = 0;
		if (args[i][j++] == '-' && args[i][j++] == 'n')
		{
			while (args[i][j])
			{
				if (args[i][j++] != 'n')
					return (option_n);
			}
			option_n++;
		}
		else
			return (option_n);
		i++;
	}
	return (option_n);
}
