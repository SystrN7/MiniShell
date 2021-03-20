/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_replace_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:11:58 by seruiz            #+#    #+#             */
/*   Updated: 2021/03/20 17:12:57 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"
#include "minishell_builtin.h"
#include "minishell_utilities.h"
#include "minishell_parser.h"

#include <unistd.h>

void	ft_assign_new_strings(t_shell_command *cmd, t_parse_mask_str *final,
		t_parse_mask_str *new)
{
	ft_managed_free(cmd->command_string);
	ft_managed_free(cmd->command_mask);
	ft_managed_free(new->str);
	ft_managed_free(new->mask);
	ft_managed_free(new);
	cmd->command_string = final->str;
	cmd->command_mask = final->mask;
	ft_managed_free(final);
}

char	*ft_init_final_string(int total_len)
{
	char	*result;

	result = ft_managed_malloc(sizeof(char) * (total_len));
	result[total_len - 1] = '\0';
	return (result);
}

t_parse_mask_str	*ft_setup_mask_str(int len)
{
	char				*new_str;
	char				*new_mask;
	t_parse_mask_str	*new;

	new = ft_managed_malloc(sizeof(t_parse_mask_str));
	new_str = ft_managed_malloc(sizeof(char) * (len));
	new_str[len - 1] = '\0';
	new_mask = ft_managed_malloc(sizeof(char) * (len));
	new_mask[len - 1] = '\0';
	new->str = new_str;
	new->mask = new_mask;
	return (new);
}

int	ft_strjoin_custom(t_shell_command *cmd, t_parse_mask_str *new,
		int var_value_len, int varname_len)
{
	int					i;
	int					j;
	int					total_len;
	t_parse_mask_str	*final;

	j = 0;
	i = ft_strlen(new->str) - var_value_len + varname_len + 1;
	total_len = ft_strlen(cmd->command_string) - varname_len + var_value_len;
	final = ft_setup_mask_str(total_len);
	while (new->str[j])
	{
		final->mask[j] = new->mask[j];
		final->str[j] = new->str[j];
		j++;
	}
	while (cmd->command_string[i])
	{
		final->mask[j] = cmd->command_mask[i];
		final->str[j] = cmd->command_string[i];
		i++;
		j++;
	}
	ft_assign_new_strings(cmd, final, new);
	return (i);
}

int	ft_is_return_code(char *varname)
{
	if (ft_strlen(varname) == 1 && varname[0] == '?')
		return (1);
	return (0);
}

char	*ft_set_var_value(char *varname, t_shell_context *context)
{
	char	*var_value;

	if (ft_is_return_code(varname) == 1)
		var_value = ft_itoa(context->last_command_return_code);
	else
		var_value = ft_strdup(env_get(context, varname));
	if (var_value == NULL)
		var_value = "";
	return (var_value);
}
