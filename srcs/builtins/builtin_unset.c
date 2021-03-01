/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 09:56:37 by fgalaup           #+#    #+#             */
/*   Updated: 2021/02/08 15:37:56 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtin.h"

/*
** Remove each variable name for given name he can remove multiple varible.
** This builtin allways return 0
*/

int		builtin_unset(t_shell_context *context, int argv, char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		ft_lst_associative_remove(&context->shared_environment, args[i], NULL);
		ft_lst_associative_remove(&context->local_environement, args[i], NULL);
	}
	return (0);
}
