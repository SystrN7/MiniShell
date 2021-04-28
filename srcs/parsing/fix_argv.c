/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 11:40:31 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/28 12:05:30 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parser.h"

int	ft_offset_argv(t_shell_command *cmd, int i, int j)
{
	j++;
	while (cmd->argv[i][j])
	{
		cmd->argv[i][j - 1] = cmd->argv[i][j];
		j++;
	}
	cmd->argv[i][j - 1] = '\0';
	return (0);
}

void	ft_fix_argv(t_shell_command *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->argv[i])
	{
		while (cmd->argv[i][j])
		{
			if (cmd->argv[i][j] == EMPTY_QUOTE)
			{
				if (j == 0 && cmd->argv[i][j + 1] == '\0')
					cmd->argv[i][j] = '\0';
				else
					j = ft_offset_argv(cmd, i, j);
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_add_nonprintable_ch(char *line, int ret, int len, int no_end_quotes)
{
	t_parse_pos	s;
	char		*result;

	s.index = 0;
	s.i = 0;
	if (no_end_quotes == -1)
		len++;
	result = ft_managed_malloc(sizeof(char) * len);
	result[len - 1] = '\0';
	while (line[s.i])
	{
		if (s.i == ret - 1)
			result[s.i++] = EMPTY_QUOTE;
		else
			result[s.index++] = line[s.i++];
	}
	result[ret - 1] = EMPTY_QUOTE;
	s.i = 0;
	while (result[s.i])
	{
		line[s.i] = result[s.i];
		s.i++;
	}
	line[s.i] = '\0';
	ft_managed_free(result);
}
