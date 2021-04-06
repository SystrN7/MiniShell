/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:45:27 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/05 17:02:10 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtin.h"

#include <sys/syslimits.h>

/*
** Print the absolute pathname of the current working directory.
** Ignore all of the argument given
*/

int	builtin_pwd(t_shell_context *context, int argc, char **args)
{
	char	path_buffer[PATH_MAX];

	(void)context;
	(void)argc;
	(void)args;
	getcwd(path_buffer, PATH_MAX);
	ft_putstr_fd(1, path_buffer);
	ft_putchar_fd(1, '\n');
	return (0);
}
