/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:26:45 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/27 10:33:41 by seruiz           ###   ########lyon.fr   */
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

void	ft_add_nonprintable_ch(char *line, int ret, int len)
{
	int		i;
	int		j;
	char	*result;

	j = 0;
	i = 0;
	result = ft_managed_malloc(sizeof(char) * len);
	result[len - 1] = '\0';
	while (line[i])
	{
		if (i == ret - 1)
			result[i++] = EMPTY_QUOTE;
		else
			result[j++] = line[i++];
	}
	result[ret - 1] = EMPTY_QUOTE;
	i = 0;
	while (result[i])
	{
		line[i] = result[i];
		i++;
	}
	line[i] = '\0';
	ft_managed_free(result);
}
