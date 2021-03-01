/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 10:23:55 by fgalaup           #+#    #+#             */
/*   Updated: 2021/02/10 14:43:21 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
** |================================ CD SPECS =================================|
** Withous params redirecting to the user home directory. (Use value of HOME).
** If params is ~ redirecting to the user home directory. (Use value of HOME).
** If params is - change to the previous directory (Use value of OLDPWD).
** If more than one argument as given in params.
** (bash: cd: Tests=kapla: No such file or directory).
** If empty args is given in frist args is just dont change of directory.
** If invalid path is specified (bash: cd: test/: No such file or directory).
** If valid path is specified change (Update OLDPWD and PWD)
*/

#include "minishell_builtin.h"

int		builtin_cd(t_shell_context *context, int argc, char **args)
{
	if (argc == 2)
	{
		if (chdir(args[1]) == -1)
		{
			error_error();
			return (1);
		}
	}
	else
	{
		error_error();
		return (1);
	}
	return (0);
}
