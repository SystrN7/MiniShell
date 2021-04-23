/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_replace_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:11:58 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/23 11:18:15 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"
#include "minishell_builtin.h"
#include "minishell_utilities.h"
#include "minishell_parser.h"

#include <unistd.h>

void	ft_assign_new_strings_argv(
	t_shell_command *cmd,
	t_parse_mask_str *final,
	t_parse_mask_str *new,
	int index
)
{
	ft_managed_free(cmd->argv[index]);
	ft_managed_free(cmd->masks[index]);
	ft_managed_free(new->str);
	ft_managed_free(new->mask);
	ft_managed_free(new);
	cmd->argv[index] = final->str;
	cmd->masks[index] = final->mask;
	ft_managed_free(final);
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

void	ft_assign_new_strings_file(
	t_redirection_list *buff,
	t_parse_mask_str *final,
	t_parse_mask_str *new
)
{
	ft_managed_free(buff->redirection_file);
	ft_managed_free(buff->mask);
	ft_managed_free(new->str);
	ft_managed_free(new->mask);
	ft_managed_free(new);
	buff->redirection_file = final->str;
	buff->mask = final->mask;
	ft_managed_free(final);
}

int	ft_strjoin_custom_file(
	t_redirection_list *buff,
	t_parse_mask_str *new,
	int var_value_len,
	int varname_len
)
{
	int					i;
	int					j;
	int					total_len;
	t_parse_mask_str	*final;

	j = 0;
	i = ft_strlen(new->str) - var_value_len + varname_len + 1;
	total_len = ft_strlen(buff->redirection_file) - varname_len + var_value_len;
	final = ft_setup_mask_str(total_len);
	while (new->str[j])
	{
		final->mask[j] = new->mask[j];
		final->str[j] = new->str[j];
		j++;
	}
	while (buff->redirection_file[i])
	{
		final->mask[j] = buff->mask[i];
		final->str[j] = buff->redirection_file[i];
		i++;
		j++;
	}
	ft_assign_new_strings_file(buff, final, new);
	return (i);
}

char	*ft_set_var_value(char *varname, t_shell_context *context)
{
	char	*var_value;

	var_value = NULL;
	if (ft_is_return_code(varname) == 1)
		var_value = ft_itoa(context->last_command_return_code);
	else
	{
		if (env_get(context, varname) != NULL)
			var_value = ft_strdup(env_get(context, varname));
	}
	if (var_value == NULL)
		var_value = "";
	return (var_value);
}
