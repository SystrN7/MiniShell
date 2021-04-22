/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:23:12 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/22 17:01:14 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parser.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	int		j;
	size_t	str1_lenght;
	size_t	str2_lenght;

	j = 0;
	str1_lenght = ft_strlen(s1);
	str2_lenght = ft_strlen(s2);
	str = ft_managed_malloc(sizeof(char) * (str1_lenght + str2_lenght + 1));
	str[str1_lenght + str2_lenght] = '\0';
	j = ft_cat(str, s1, 0);
	j = ft_cat(str, s2, j);
	ft_managed_free(s1);
	ft_managed_free(s2);
	return (str);
}

void	ft_fill_mask(char *mask, char c, int len, t_shell_command *str_struct)
{
	while (len >= 0)
	{
		mask[len] = c;
		len--;
	}
	if (str_struct->command_mask == NULL)
		str_struct->command_mask = mask;
	else
		str_struct->command_mask = ft_strjoin_free(str_struct->command_mask,
				mask);
}

void	ft_fill_str(char *line, int j, int len, t_shell_command *str_struct)
{
	char	*s;
	int		x;

	x = 0;
	s = ft_managed_malloc(sizeof(char) * len + 1);
	s[len] = '\0';
	while (x < len)
	{
		s[x] = line[j];
		x++;
		j++;
	}
	if (str_struct->command_string == NULL)
		str_struct->command_string = s;
	else
		str_struct->command_string = ft_strjoin_free(str_struct->command_string,
				s);
}

int	ft_single_quote(char *line, int j, t_shell_command *str_struct)
{
	int		ret;
	char	*mask;
	int		no_end_quote;

	no_end_quote = 0;
	ret = j + 1;
	while (line[ret] && line[ret] != '\'')
		ret++;
	if (ret == (int)ft_strlen(line))
		no_end_quote = -1;
	mask = ft_managed_malloc(sizeof(char) * (ret - j));
	mask[ret - j - 1] = '\0';
	ft_fill_mask(mask, '1', ret - j - 2, str_struct);
	ft_fill_str(line, j + 1, ret - j - 1, str_struct);
	return (ret + 1 + no_end_quote);
}

int	ft_double_quote(char *line, int j, t_shell_command *str_struct)
{
	int		ret;
	int		no_end_quotes;
	char	*mask;

	no_end_quotes = 0;
	ret = j + 1;
	while ((line[ret] && (line[ret] != '\"' && ret - 1 >= 0))
		|| line[ret - 1] == '\\')
		ret++;
	if (ret == (int)ft_strlen(line))
		no_end_quotes = -1;
	mask = ft_managed_malloc(sizeof(char) * (ret - j));
	mask[ret - j - 1] = '\0';
	ft_fill_mask(mask, '2', ret - j - 2, str_struct);
	ft_fill_str(line, j + 1, ret - j - 1, str_struct);
	return (ret + 1 + no_end_quotes);
}
