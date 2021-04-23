/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_replace_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:16:19 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/23 12:47:47 by seruiz           ###   ########lyon.fr   */
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

int	ft_strjoin_custom_argv(
	t_shell_command *cmd,
	t_parse_mask_str *new,
	int len[2],
	int index
)
{
	int					i;
	int					j;
	int					total_len;
	t_parse_mask_str	*final;

	j = 0;
	i = ft_strlen(new->str) - len[0] + len[1] + 1;
	total_len = ft_strlen(cmd->argv[index]) - len[1] + len[0];
	final = ft_setup_mask_str(total_len);
	while (new->str[j])
	{
		final->mask[j] = new->mask[j];
		final->str[j] = new->str[j];
		j++;
	}
	while (cmd->argv[index][i])
	{
		final->mask[j] = cmd->masks[index][i];
		final->str[j] = cmd->argv[index][i];
		i++;
		j++;
	}
	ft_assign_new_strings_argv(cmd, final, new, index);
	return (i);
}
