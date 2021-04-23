/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_replace_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:16:19 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/23 11:18:20 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parser.h"

void	ft_is_empty_file(t_parse_mask_str *new, int k, int j)
{
	if (j == 0 && k == 0)
	{
		new->str[0] = '\0';
		new->mask[0] = '\0';
	}
}

void	ft_is_empty_argv(t_parse_mask_str *new, int k, int j)
{
	if (j == 0 && k == 0)
	{
		new->str[0] = '\0';
		new->mask[0] = '\0';
	}
}

int	ft_is_return_code(char *varname)
{
	if (ft_strlen(varname) == 1 && varname[0] == '?')
		return (1);
	return (0);
}

char	*ft_init_final_string(int total_len)
{
	char	*result;

	result = ft_managed_malloc(sizeof(char) * (total_len));
	result[total_len - 1] = '\0';
	return (result);
}
