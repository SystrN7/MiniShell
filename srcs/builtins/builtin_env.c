/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 09:53:40 by fgalaup           #+#    #+#             */
/*   Updated: 2021/02/10 14:41:27 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtin.h"

int		builtin_env(t_shell_context *context, int argv, char **args)
{
	t_list			*it;
	t_associative	*var;

	while (it)
	{
		var = (t_associative*)var;
		ft_printf("%s=%s\n", var->key, var->value);
		it = it->next;
	}
	return (0);
}
