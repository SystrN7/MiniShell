/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_filename.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:54:09 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/28 12:54:27 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parser.h"

int	ft_offset_filename(t_redirection_list *buff, int j)
{
	j++;
	while (buff->redirection_file[j])
	{
		buff->redirection_file[j - 1] = buff->redirection_file[j];
		j++;
	}
	buff->redirection_file[j - 1] = '\0';
	return (0);
}

int	ft_fix_filename(t_redirection_list	*buff)
{
	int	j;

	j = 0;
	while (buff->redirection_file[j])
	{
		if (buff->redirection_file[j] == EMPTY_QUOTE)
		{
			if (j == 0 && buff->redirection_file[j + 1] == '\0')
				buff->redirection_file[j] = '\0';
			else
				j = ft_offset_filename(buff, j);
		}
		j++;
	}
	return (0);
}
