/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:40:49 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/15 11:12:24 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utilities.h"
#include "minishell_type.h"

t_bool	env_is_assignment(const char *value)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(value[i]) || value[i] != '_')
		return (FALSE);
	while (ft_isalnum(value[i]) || value[i] != '_')
		i++;
	if (value[i] == '=')
		return (TRUE);
	return (FALSE);
}

/**
 * Return true if is a legal shell `identifier'; that is, it consists
 * solely of letters, digits, and underscores, and does not begin with a
 * digit and if ending with '\0' or '='.
 **/

t_bool	env_is_identifier(const char *value)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(value[i]) && value[i] != '_')
		return (FALSE);
	while (ft_isalnum(value[i]) || value[i] == '_')
		i++;
	if (value[i] == '\0' || value[i] == '=')
		return (TRUE);
	return (FALSE);
}
