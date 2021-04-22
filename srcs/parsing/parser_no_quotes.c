/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_no_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:23:21 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/22 15:58:54 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parser.h"

void	ft_fill_str_no_quotes(char *line, int j, int len, t_shell_command *str_struct)
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
		{
			s[k] = line[j];
			k++;
			j++;
		}
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
	int		ret;
	int		backslash;
	char	*mask;

	ret = j;
	backslash = 0;
	while (line[ret] && line[ret] != '\"' && line[ret] != '\''
		&& ft_is_separator(line, ret) == 0)
	{
		if (line[ret] == '\\')
		{
			if (line[ret + 1] == '\0')
			{
				line[ret] = '\0';
				ret--;
			}
			else
			{
				backslash++;
				ret++;
			}
		}
		ret++;
	}
	mask = ft_managed_malloc(sizeof(char) * (ret - j + 1 - backslash));
	mask[ret - j - backslash] = '\0';
	ft_fill_mask_no_quotes(line, mask, j, str_struct);
	ft_fill_str_no_quotes(line, j, ret - j - backslash, str_struct);
	return (ret);
}
