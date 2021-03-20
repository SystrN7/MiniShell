/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_manip.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felix <felix@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 12:26:14 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/16 15:55:43 by felix            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utilities.h"

void	*env_get(t_shell_context *context, const char *key)
{
	return (ft_lst_associative_get(context->shared_environment, key));
}

void	env_set(t_shell_context *context, char *key, char *value)
{
	ft_lst_associative_set(&context->shared_environment, key, value);
}

void	env_clear(t_list **env)
{
	ft_lstclear(env, ft_lst_associative_del_free);
}
