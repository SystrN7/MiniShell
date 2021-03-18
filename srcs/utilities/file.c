/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:40:36 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/18 16:18:55 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/errno.h>

#include "minishell_utilities.h"

t_bool	is_command(const char *path)
{
	struct stat	file_properties;

	if (stat(path, &file_properties) == -1)
	{
		errno = 0;
		return (FALSE);
	}
	return (TRUE);
}
