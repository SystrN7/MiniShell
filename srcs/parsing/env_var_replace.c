/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:10:28 by seruiz            #+#    #+#             */
/*   Updated: 2021/03/20 17:05:33 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"
#include "minishell_builtin.h"
#include "minishell_utilities.h"
#include "minishell_parser.h"

#include <unistd.h>

void	ft_assign_new_strings(t_shell_command *cmd, t_parse_mask_str *final, t_parse_mask_str *new)
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

int	ft_strjoin_custom(t_shell_command *cmd, t_parse_mask_str *new, int var_value_len, int varname_len)
{
	int		i;
	int		j;
	int		total_len;
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

void	ft_is_empty(t_parse_mask_str *new, int k, int j)
{
	if (j == 0 && k == 0)
	{
		new->str[0] = '\0';
		new->mask[0] = '\0';
	}
}

int	ft_cpy_before_dollard(t_shell_command *cmd, t_parse_mask_str *new, int j)
{
	if (!(cmd->command_string[0] == '$'))
	{
		while (cmd->command_string[j] != '$')
		{
			new->str[j] = cmd->command_string[j];
			new->mask[j] = cmd->command_mask[j];
			j++;
		}
	}
	return (j);
}

int	ft_replace_in_struct(t_shell_context *context,
	t_shell_command *cmd, int i, char *varname)
{
	int					j;
	int					k;
	t_parse_mask_str	*new;
	char				*var_value;

	j = 0;
	k = 0;
	var_value = ft_set_var_value(varname, context);
	new = ft_setup_mask_str(i + ft_strlen(var_value));
	j = ft_cpy_before_dollard(cmd, new, j);
	while (var_value[k])
	{
		new->mask[j] = cmd->command_mask[j - k];
		new->str[j++] = var_value[k++];
	}
	ft_is_empty(new, k, j);
	ft_strjoin_custom(cmd, new, ft_strlen(var_value), ft_strlen(varname));
	ft_managed_free(var_value);
	return (j);
}

int	ft_replace_var(t_shell_context *context, t_shell_command *cmd, int i)
{
	char	mask;
	int		j;
	char	*varname;

	j = i;
	mask = cmd->command_mask[i];
	while (cmd->command_string[j] && cmd->command_mask[j] == mask
		&& (ft_isalnum(cmd->command_string[j]) == 1
			|| cmd->command_string[j] == '_' || cmd->command_string[j] == '?'))
		j++;
	varname = ft_managed_malloc(sizeof(char) * j - i + 1);
	varname[j - i] = '\0';
	j = i;
	while (cmd->command_string[j] && cmd->command_mask[j] == mask
		&& (ft_isalnum(cmd->command_string[j]) == 1
			|| cmd->command_string[j] == '_' || cmd->command_string[j] == '?'))
	{
		varname[j - i] = cmd->command_string[j];
		j++;
	}
	j = ft_replace_in_struct(context, cmd, i, varname);
	ft_managed_free(varname);
	return (j);
}

void	ft_treat_var(t_shell_context *context, t_shell_command *cmd)
{
	int	i;

	i = 0;
	if (!(cmd->command_string == NULL))
	{
		while (cmd->command_string[i])
		{
			if (cmd->command_string[i] == '$' && cmd->command_mask[i] != '1')
				i = ft_replace_var(context, cmd, i + 1);
			else
				i++;
		}
	}
}
