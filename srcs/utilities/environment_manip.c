/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_manip.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 12:26:14 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/15 14:19:59 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utilities.h"

void	*env_get(t_shell_context *context, const char *key)
{
	return (ft_lst_associative_get(context->shared_environment, key));
}

void	env_set(t_shell_context *context, char *key, char *value)
{
	ft_managed_free(env_get(context, key));
	ft_lst_associative_set(&context->shared_environment, key, value);
}

void	env_clear(t_list **env)
{
	ft_lstclear(env, ft_lst_associative_del_free);
}
