/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_manip.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 12:26:14 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/09 14:36:02 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utilities.h"

void	*env_get(t_shell_context *context, char *key)
{
	void	*value;

	value = ft_lst_associative_get(context->local_environement, key);
	if (value == NULL)
		value = ft_lst_associative_get(context->shared_environment, key);
	return (value);
}

void	env_clear(t_list **env)
{
	ft_lstclear(env, ft_lst_associative_del_free);
}
