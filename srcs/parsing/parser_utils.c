/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:26:45 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/23 12:28:38 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parser.h"

int	ft_cat(char *dest, char *s, int j)
{
	int	i;

	i = 0;
	while (s[i])
	{
		dest[j] = s[i];
		i++;
		j++;
	}
	return (j);
}

t_parse_struct	*ft_setup_parse_struct(t_parse_struct	*ret)
{
	ft_memset(ret, 0, sizeof(t_parse_struct));
	ret->node = ft_binarytree_node_create(NULL);
	ret->root = ret->node;
	return (ret);
}

int	ft_root_val_null(t_node_binary **root, t_shell_command **str_root,
	char *line, int j)
{
	(*str_root) = ft_new_str_struct();
	(*root)->value = *str_root;
	return (ft_first_command(line, j, root));
}
