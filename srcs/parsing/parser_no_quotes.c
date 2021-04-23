/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_no_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:23:21 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/23 13:41:16 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parser.h"

void	ft_fill_str_no_quotes(
	char *line,
	int j,
	int len,
	t_shell_command *str_struct
)
{
	char	*s;
	int		k;

	k = 0;
	s = ft_managed_malloc(sizeof(char) * len + 1);
	s[len] = '\0';
	while (line[j] && line[j] != '\"' && line[j] != '\''
		&& ft_is_separator(line, j) == 0)
	{
		if (line[j] == '\\')
		{
			s[k] = line[j + 1];
			k++;
			j += 2;
		}
		else
			s[k++] = line[j++];
	}
	if (str_struct->command_string == NULL)
		str_struct->command_string = s;
	else
		str_struct->command_string = ft_strjoin_free(str_struct->command_string,
				s);
}

void	ft_fill_mask_no_quotes(char *line, char *mask, int j,
			t_shell_command *str_struct)
{
	int		k;

	k = 0;
	while (line[j] && line[j] != '\"' && line[j] != '\''
		&& ft_is_separator(line, j) == 0)
	{
		if (line[j] == '\\')
		{
			mask[k] = '1';
			k++;
			j += 2;
		}
		else
		{
			mask[k] = '0';
			k++;
			j++;
		}
	}
	if (str_struct->command_mask == NULL)
		str_struct->command_mask = mask;
	else
		str_struct->command_mask = ft_strjoin_free(str_struct->command_mask,
				mask);
}

int	ft_no_quote(char *line, int j, t_shell_command *str_struct)
{
	char				*mask;
	t_parse_backslash	s;

	s.ret = j;
	s.backslash = 0;
	while (line[s.ret] && line[s.ret] != '\"' && line[s.ret] != '\''
		&& ft_is_separator(line, s.ret) == 0)
	{
		if (line[s.ret] == '\\')
		{
			if (line[s.ret + 1] == '\0')
				line[s.ret--] = '\0';
			else
			{
				s.backslash++;
				s.ret++;
			}
		}
		s.ret++;
	}
	mask = ft_managed_malloc(sizeof(char) * (s.ret - j + 1 - s.backslash));
	mask[s.ret - j - s.backslash] = '\0';
	ft_fill_mask_no_quotes(line, mask, j, str_struct);
	ft_fill_str_no_quotes(line, j, s.ret - j - s.backslash, str_struct);
	return (s.ret);
}
