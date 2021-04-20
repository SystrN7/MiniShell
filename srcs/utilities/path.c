/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:05:16 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/20 10:57:12 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utilities.h"

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

char	*path_get_binary_path(char *env_path, char *binary_name)
{
	size_t	i;
	char	**binaries_location;
	char	*path[4];

	i = 0;
	if (env_path == NULL || binary_name == NULL)
		return (NULL);
	binaries_location = ft_split(env_path, ':');
	while (binaries_location[i])
	{
		path[0] = binaries_location[i];
		if (path_find_binary(binaries_location[i], binary_name))
		{
			i = 1;
			if (path[0][ft_strlen(path[0]) - 1] != '/')
				path[i++] = "/";
			path[i++] = binary_name;
			path[i++] = NULL;
			path[0] = ft_2d_merge(path);
			ft_2d_free((void **)binaries_location);
			return (path[0]);
		}
		i++;
	}
	ft_2d_free((void **)binaries_location);
	return (NULL);
}

t_bool	path_find_binary(char *directory_name, char *binary_name)
{
	int				result;
	DIR				*directory;
	struct dirent	*dir_content;
	size_t			binary_name_lenght;

	result = FALSE;
	directory = opendir(directory_name);
	binary_name_lenght = ft_strlen(binary_name);
	if (!directory)
		return (result);
	dir_content = readdir(directory);
	while (dir_content && !result)
	{
		if (dir_content->d_namlen == binary_name_lenght
			&& !ft_stricmp(dir_content->d_name, binary_name)
		)
			result = TRUE;
		dir_content = readdir(directory);
	}
	closedir(directory);
	return (result);
}
