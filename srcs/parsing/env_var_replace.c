/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:10:28 by seruiz            #+#    #+#             */
/*   Updated: 2021/03/17 15:42:28 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"
#include "minishell_builtin.h"
#include "minishell_utilities.h"
#include "minishell_parser.h"

#include <unistd.h>

int	ft_strjoin_custom(t_shell_command *cmd, char *new_str, char *new_mask, int var_value_len, int varname_len)
{
	int		i;
	int		j;
	int		total_len;
	char	*final_str;
	char	*final_mask;

	j = 0;
	i = ft_strlen(new_str) - var_value_len + varname_len + 1;
	total_len = ft_strlen(cmd->command_string) - varname_len + var_value_len;
	final_str = ft_managed_malloc(sizeof(char) * (total_len));
	final_mask = ft_managed_malloc(sizeof(char) * (total_len));
	final_mask[total_len - 1] = '\0';
	final_str[total_len - 1] = '\0';
	while(new_str[j])
	{
		final_mask[j] = new_mask[j];
		final_str[j] = new_str[j];
		j++;
	}
	while (cmd->command_string[i])
	{
		final_mask[j] = cmd->command_mask[i];
		final_str[j] = cmd->command_string[i];
		i++;
		j++;
	}
	ft_managed_free(cmd->command_string);
	ft_managed_free(cmd->command_mask);
	ft_managed_free(new_str);
	ft_managed_free(new_mask);
	cmd->command_string = final_str;
	cmd->command_mask = final_mask;
	printf("\nFinal str = %s\n", final_str);
	printf("\nFinal mask= %s\n", final_mask);
	return (i);
}

int	ft_replace_in_struct(t_shell_context *context, t_shell_command *cmd, int i, char *varname)
{
	int		j;
	int		k;
	char	*new_str;
	char	*new_mask;
	char	*var_value;

	j = 0;
	k = 0;
	var_value = env_get(context, varname);
	if (var_value == NULL)
		var_value = "";
	printf("var_value = %s\n", var_value);
	new_str = ft_managed_malloc(sizeof(char) * (i + ft_strlen(var_value)));
	new_str[i + ft_strlen(var_value) - 1] = '\0';
	new_mask = ft_managed_malloc(sizeof(char) * (i + ft_strlen(var_value)));
	new_mask[i + ft_strlen(var_value) - 1] = '\0';
	printf("i + ft_strlen(var_value = %lu\n", i + ft_strlen(var_value));
	printf("test\ncmd[j] = %c\n", cmd->command_string[j]);
	if (!(cmd->command_string[0] == '$'))
	{
		while (cmd->command_string[j] != '$' || cmd->command_string[j - 1] == '\\')
		{
			new_str[j] = cmd->command_string[j];
			new_mask[j] = cmd->command_mask[j];
			j++;
		}
	}
	//printf("new str inbetween = %s\n", new_str);
	printf("wesh\n");
	while (var_value[k])
	{
		new_str[j] = var_value[k];
		new_mask[j] = cmd->command_mask[j - k];
		j++;
		k++;
	}
	if (j == 0 && k == 0)
	{
		new_str[0] = '\0';
		new_mask[0] = '\0';
	}
	printf("new_str = %s\n", new_str);
	printf("new_mask= %s\n", new_mask);
	ft_strjoin_custom(cmd, new_str, new_mask, ft_strlen(var_value), ft_strlen(varname));
	return (j);
}

int	ft_replace_var(t_shell_context *context, t_shell_command *cmd, int i)
{
	char	mask;
	int		j;
	char	*varname;

	j = i;
	mask = cmd->command_mask[i];
	while (cmd->command_string[j] && cmd->command_mask[j] == mask && (ft_isalnum(cmd->command_string[j]) == 1 || cmd->command_string[j] == '_'))
		j++;
	varname = ft_managed_malloc(sizeof(char) * j - i + 1);
	varname[j - i] = '\0';
	j = i;
	while (cmd->command_string[j] && cmd->command_mask[j] == mask && (ft_isalnum(cmd->command_string[j]) == 1 || cmd->command_string[j] == '_'))
	{
		varname[j - i] = cmd->command_string[j];
		j++;
	}
	printf("varname = %s\n", varname);
	j = ft_replace_in_struct(context, cmd, i, varname);
	ft_managed_free(varname);
	return (j);
}

void	ft_treat_var(t_shell_context *context, t_shell_command *cmd)
{
	int	i;

	i = 0;
	printf("str = %s\n", cmd->command_string);
	printf("mask= %s\n", cmd->command_mask);
	if (!(cmd->command_string == NULL))
	{
		while (cmd->command_string[i])
		{
			if (cmd->command_string[i] == '$' && cmd->command_mask[i] != '1'
				&& (i == 0 || cmd->command_string[i - 1] != '\\'))
				i = ft_replace_var(context, cmd, i + 1);
			else
				i++;
		}
	}
}

/*
void	ft_parse(t_shell_command cmd)
{
	int	i;

	i = 0;
	printf("str = %s\n", cmd.command_string);
	printf("mask= %s\n", cmd.command_mask);
	while (cmd.command_string[i])
	{
		if (cmd.command_string[i] == '$' && cmd.command_mask[i] != '1')
			i = ft_replace_var(cmd, i + 1);
		else
			i++;
	}
}

int main(int argc, char **argv)
{
    t_shell_command cmd;

    cmd.str = argv[1];
    cmd.mask = argv[2];
    ft_parse(cmd);
    return (1);
}
*/