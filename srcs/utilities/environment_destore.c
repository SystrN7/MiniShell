/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement_destore.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 12:23:57 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/06 12:25:39 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utilities.h"
#include "minishell_type.h"

char	*env_destore(t_associative *env_link)
{
	char	*env_row[4];

	if (env_link == NULL)
		return (NULL);
	env_row[0] = env_link->key;
	env_row[1] = "=";
	env_row[2] = env_link->value;
	env_row[3] = NULL;
	return (ft_2d_merge(env_row));
}

char	**env_destore_all(t_list *env_list)
{
	size_t	list_size;
	char	**env;
	int		i;
	t_list	*it;

	i = 0;
	it = env_list;
	list_size = ft_lstsize(env_list);
	env = ft_calloc(list_size + 1, sizeof(void *));
	if (env == NULL)
		return (env);
	while (it)
	{
		env[i] = env_destore(it->content);
		it = it->next;
		i++;
	}
	return (env);
}
