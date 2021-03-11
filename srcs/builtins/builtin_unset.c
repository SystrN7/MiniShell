/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 09:56:37 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/11 12:55:32 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtin.h"

/*
** Remove each variable name for given name he can remove multiple varible.
** This builtin allways return 0
*/

int		builtin_unset(t_shell_context *cnt, int argc, char **args)
{
	size_t	i;

	(void)argc;
	i = 0;
	while (args[i])
	{
		if (env_is_identifier(args[i]))
		{
			ft_lst_associative_remove(&cnt->shared_environment, args[i], free);
			ft_lst_associative_remove(&cnt->local_environement, args[i], free);
		}
		else
			error_occure("Unvalid env_is_identifier");
	}
	return (0);
}
