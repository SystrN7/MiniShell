/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_store.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 12:24:23 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/16 17:11:33 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utilities.h"
#include "minishell_type.h"

t_list	*env_store(char *env[])
{
	int				i;
	t_list			*env_list;
	t_associative	splited_row;

	i = 0;
	env_list = NULL;
	if (env == NULL)
		return (NULL);
	while (env[i])
	{
		splited_row = env_key_value_split(env[i]);
		ft_lst_associative_set(&env_list, splited_row.key, splited_row.value);
		i++;
	}
	return (env_list);
}

t_asso	env_key_value_split(char *env_row)
{
	t_associative	splited_row;
	char			*key_value_separator;

	key_value_separator = ft_strchr(env_row, '=');
	if (key_value_separator)
		splited_row.value = ft_strdup(key_value_separator + 1);
	else
		splited_row.value = NULL;
	splited_row.key = ft_substr(env_row, 0, key_value_separator - env_row);
	return (splited_row);
}
