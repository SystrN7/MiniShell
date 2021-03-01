/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:40:49 by fgalaup           #+#    #+#             */
/*   Updated: 2021/02/20 11:28:24 by fgalaup          ###   ########lyon.fr   */
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
	size_t			row_lenght;

	row_lenght = ft_strlen(env_row);
	key_value_separator = ft_strchr(env_row, '=');
	splited_row.value = ft_strdup(key_value_separator + 1);
	splited_row.key = ft_substr(env_row, 0, key_value_separator - env_row);
	return (splited_row);
}

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
