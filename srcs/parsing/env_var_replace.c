/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:10:28 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/07 17:06:57 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"
#include "minishell_builtin.h"
#include "minishell_utilities.h"
#include "minishell_parser.h"

#include <unistd.h>

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
	printf("OLD VARNAME = %s\n", varname);
	j = ft_replace_in_struct(context, cmd, i, varname);
	ft_managed_free(varname);
	return (j);
}

void	ft_replace_argv(char *var_value, char *varname, t_shell_command *cmd, int i)
{
	char	*new_argv;
	int		final_len;
	int		j;

	j = 0;
	final_len = ft_strlen(cmd->argv[i]) - ft_strlen(varname) + ft_strlen(var_value);
	new_argv = ft_managed_malloc(sizeof(char) * final_len + 1);
	while (cmd->argv[i][j] != '$' && cmd->command_mask[j] != '1')
	{
		j++;
	}
}

void	ft_test(t_shell_context *context, t_shell_command *cmd, int i, int len, int j)
{
	char	mask;
	int		varlen;
	char	*varname;
	char	*var_value;
	int		k;

	k = 0;
	mask = cmd->command_mask[len];
	printf("len = %d\nj   = %d\n", len, j);
	j++;
	varlen = j;
	while (cmd->argv[i][j] && cmd->command_mask[++len] == mask
		&& (ft_isalnum(cmd->argv[i][j]) == 1
			|| cmd->argv[i][j] == '_' || cmd->argv[i][j] == '?'))
		j++;
	varlen = j - varlen;
	printf("Varlen = %d\n", varlen);
	varname = ft_managed_malloc(sizeof(char) * varlen + 1);
	varname[varlen] = '\0';
	j = j - varlen;
	while (k < varlen)
	{
		varname[k] = cmd->argv[i][j];
		k++;
		j++;
	}
	printf("Varname = %s\n", varname);
	printf("len = %zu\n", ft_strlen(varname));
	var_value = ft_set_var_value(varname, context);
	ft_replace_argv(var_value, varname, cmd, i);
	printf("Var = %s\n", var_value);
}

void	ft_treat_var(t_shell_context *context, t_shell_command *cmd)
{
	int	i;
	int	j;
	int	len;
	t_redirection_list	*buff;

	i = 0;
	j = 0;
	len = 0;
	while (cmd->argv[i])
	{
		while (cmd->argv[i][j])
		{
			if (cmd->argv[i][j] == '$' && cmd->command_mask[len + j] != '1')
			{
				printf("Found Var to replace\nindex = %d\n", len + j);
				ft_test(context, cmd, i, len + j, j);
				//replace var in argv
			}
			j++;
		}
		len += j;
		while (cmd->command_string[len] == ' ')
			len++;
		j = 0;
		i++;
	}
	i = 0;
	j = 0;
	buff = *cmd->redirection;
	//while (cmd->redirection[i]->redirection_file)
	while (buff)
	{
		printf("filename = %s\n", buff->redirection_file);
		while (buff->redirection_file[j])
		{
			if (buff->redirection_file[j] == '$'
				&& buff->mask[j] != '1')
			{
				printf("Filename : %s\n", buff->redirection_file);
				printf("Mask     : %s\n", buff->mask);
			}
			j++;
		}
		i++;
		j = 0;
		buff = buff->next;
	}

/*
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
*/
}
