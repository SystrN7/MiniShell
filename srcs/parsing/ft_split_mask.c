/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mask.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:19:30 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/28 12:35:09 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"
#include "minishell_builtin.h"
#include "minishell_utilities.h"
#include "minishell_parser.h"

#include <unistd.h>

int	ft_malloc_argvmask(t_shell_command *cmd, int j, int size)
{
	cmd->argv[j] = ft_managed_malloc(sizeof(char) * (size + 1));
	cmd->masks[j] = ft_managed_malloc(sizeof(char) * (size + 1));
	return (1);
}

int	ft_fill_argvmask(t_shell_command *cmd, int j, int i, int size)
{
	int	k;

	k = 0;
	while (size > 0)
	{
		cmd->masks[j][k] = cmd->command_mask[i];
		cmd->argv[j][k] = cmd->command_string[i];
		i++;
		k++;
		size--;
	}
	cmd->masks[j][k] = '\0';
	cmd->argv[j][k] = '\0';
	return (1);
}

int	ft_fill_argv(t_shell_command *cmd, char c)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = 0;
	while (cmd->command_string[i])
	{
		while ((cmd->command_string[i + size] != c
				&& cmd->command_string[i + size] != '\0')
			|| (cmd->command_mask[i + size] != '0'
				&& cmd->command_mask[i + size] != '\0'))
			size++;
		if (size > 0)
		{
			ft_malloc_argvmask(cmd, j, size);
			ft_fill_argvmask(cmd, j, i, size);
			j++;
			i += size - 1;
			size = 0;
		}
		i++;
	}
	return (1);
}

static	int	ft_count_line(char const *s, char const *mask, char c)
{
	int	i;
	int	ligne;

	ligne = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while ((s[i] != c && s[i] != '\0')
				|| (mask[i] != '0' && mask[i] != '\0'))
				i++;
			ligne++;
		}
		else
			i++;
	}
	return (ligne);
}

int	ft_split_mask(t_shell_command *cmd, char c)
{
	int		ligne;

	if (cmd->command_string == NULL)
		return (0);
	ligne = ft_count_line(cmd->command_string, cmd->command_mask, c);
	cmd->argv = ft_managed_malloc(sizeof(char *) * (ligne + 1));
	cmd->masks = ft_managed_malloc(sizeof(char *) * (ligne + 1));
	if (ft_fill_argv(cmd, c) == 0)
		return (0);
	cmd->argv[ligne] = 0;
	cmd->masks[ligne] = 0;
	return (1);
}
