/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:10:28 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/23 11:17:07 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"
#include "minishell_builtin.h"
#include "minishell_utilities.h"
#include "minishell_parser.h"

#include <unistd.h>

int	ft_cpy_before_dollard_argv(
	t_shell_command *cmd,
	t_parse_mask_str *new,
	int j,
	int index
)
{
	if (!(cmd->argv[index][0] == '$'))
	{
		while (cmd->argv[index][j] != '$')
		{
			new->str[j] = cmd->argv[index][j];
			new->mask[j] = cmd->masks[index][j];
			j++;
		}
	}
	return (j);
}

int	ft_replace_in_struct_argv(
	t_shell_context *context,
	t_shell_command *cmd,
	int i,
	char *varname,
	int index
)
{
	int					j;
	int					k;
	t_parse_mask_str	*new;
	char				*var_value;
	int					len[2];

	j = 0;
	k = 0;
	var_value = ft_set_var_value(varname, context);
	new = ft_setup_mask_str(i + ft_strlen(var_value));
	j = ft_cpy_before_dollard_argv(cmd, new, j, index);
	while (var_value[k])
	{
		new->mask[j] = cmd->masks[index][j - k];
		new->str[j++] = var_value[k++];
	}
	ft_is_empty_argv(new, k, j);
	len[0] = ft_strlen(var_value);
	len[1] = ft_strlen(varname);
	ft_strjoin_custom_argv(cmd, new, len, index);
	ft_managed_free(var_value);
	return (j);
}

int	ft_replace_var_argv(
	t_shell_context *context,
	t_shell_command *cmd,
	int i,
	int index
)
{
	char	mask;
	int		j;
	char	*varname;

	j = i;
	mask = cmd->masks[index][i];
	while (cmd->argv[index][j] && cmd->masks[index][j] == mask
		&& (ft_isalnum(cmd->argv[index][j]) == 1
			|| cmd->argv[index][j] == '_' || cmd->argv[index][j] == '?'))
		j++;
	varname = ft_managed_malloc(sizeof(char) * j - i + 1);
	varname[j - i] = '\0';
	j = i;
	while (cmd->argv[index][j] && cmd->masks[index][j] == mask
		&& (ft_isalnum(cmd->argv[index][j]) == 1
			|| cmd->argv[index][j] == '_' || cmd->argv[index][j] == '?'))
	{
		varname[j - i] = cmd->argv[index][j];
		j++;
	}
	j = ft_replace_in_struct_argv(context, cmd, i, varname, index);
	ft_managed_free(varname);
	return (j);
}

int	ft_cpy_before_dollard_file(
	t_redirection_list *buff,
	t_parse_mask_str *new, int j
)
{
	if (!(buff->redirection_file[0] == '$'))
	{
		while (buff->redirection_file[j] != '$')
		{
			new->str[j] = buff->redirection_file[j];
			new->mask[j] = buff->mask[j];
			j++;
		}
	}
	return (j);
}

int	ft_replace_in_struct_file(
	t_shell_context *context,
	t_redirection_list *buff,
	int i,
	char *varname
)
{
	int					j;
	int					k;
	t_parse_mask_str	*new;
	char				*var_value;

	j = 0;
	k = 0;
	var_value = ft_set_var_value(varname, context);
	new = ft_setup_mask_str(i + ft_strlen(var_value));
	j = ft_cpy_before_dollard_file(buff, new, j);
	while (var_value[k])
	{
		new->mask[j] = buff->mask[j - k];
		new->str[j++] = var_value[k++];
	}
	ft_is_empty_argv(new, k, j);
	ft_strjoin_custom_file(buff, new, ft_strlen(var_value), ft_strlen(varname));
	ft_managed_free(var_value);
	return (j);
}

int	ft_replace_var_file(
	t_shell_context *context,
	t_redirection_list *buff, int i
)
{
	char	mask;
	int		j;
	char	*varname;

	j = i;
	mask = buff->mask[i];
	while (buff->redirection_file[j] && buff->mask[j] == mask
		&& (ft_isalnum(buff->redirection_file[j]) == 1
			|| buff->redirection_file[j] == '_'
			|| buff->redirection_file[j] == '?'))
		j++;
	varname = ft_managed_malloc(sizeof(char) * j - i + 1);
	varname[j - i] = '\0';
	j = i;
	while (buff->redirection_file[j] && buff->mask[j] == mask
		&& (ft_isalnum(buff->redirection_file[j]) == 1
			|| buff->redirection_file[j] == '_'
			|| buff->redirection_file[j] == '?'))
	{
		varname[j - i] = buff->redirection_file[j];
		j++;
	}
	j = ft_replace_in_struct_file(context, buff, i, varname);
	ft_managed_free(varname);
	return (j);
}

void	ft_replace_filenames(
	t_shell_context *context,
	t_shell_command *cmd
)
{
	int					j;
	t_redirection_list	*buff;

	j = 0;
	buff = cmd->redirection;
	while (buff)
	{
		while (buff->redirection_file[j])
		{
			if (buff->redirection_file[j] == '$' && buff->mask[j] != '1')
				j = ft_replace_var_file(context, buff, j + 1);
			else
				j++;
		}
		j = 0;
		buff = buff->next;
	}
}

void	ft_treat_var(t_shell_context *context, t_shell_command *cmd)
{
	int					i;
	int					j;

	i = 0;
	j = 0;
	while (cmd->argv[i])
	{
		while (cmd->argv[i][j])
		{
			if (cmd->argv[i][j] == '$' && cmd->masks[i][j] != '1')
				j = ft_replace_var_argv(context, cmd, j + 1, i);
			else
				j++;
		}
		j = 0;
		i++;
	}
	ft_replace_filenames(context, cmd);
}
