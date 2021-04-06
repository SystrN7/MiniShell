/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 09:56:37 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/05 17:02:06 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtin.h"

/*
** Remove each variable name for given name he can remove multiple varible.
** This builtin allways return 0
*/

int	builtin_unset(t_shell_context *cnt, int argc, char **args)
{
	size_t	i;

	(void)argc;
	i = 1;
	while (args[i])
	{
		if (env_is_identifier(args[i]))
			ft_lst_associative_remove(
				&cnt->shared_environment,
				args[i],
				ft_managed_free);
		else
			error_builtin(
				cnt,
				ERROR_ENV_INVALID_IDENTIFIER, 1,
				args[path], NULL, args[i]);
		i++;
	}
	return (cnt->last_command_return_code);
}
