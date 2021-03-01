/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:39:17 by fgalaup           #+#    #+#             */
/*   Updated: 2021/02/08 15:34:36 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_error.h"

int	ft_error(int error_code)
{
	int i;

	i = 0;
	if (error_code == ERROR_STD)
		return (ft_std_error());
	while (error_messages[i].message != NULL)
	{
		if (error_messages[i].code == error_code)
		{
			ft_printf_fd(2, "Error\n : %s\n", error_messages[i].message);
			break ;
		}
		i++;
	}
	return (error_code);
}

int	ft_std_error(void)
{
	perror("Error\n ");
	return (errno);
}
