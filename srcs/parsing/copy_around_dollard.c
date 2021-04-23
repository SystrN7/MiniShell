/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_around_dollard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:38:39 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/23 12:39:53 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"
#include "minishell_builtin.h"
#include "minishell_utilities.h"
#include "minishell_parser.h"

#include <unistd.h>

int	ft_cpy_before_dollard_argv(
	t_shell_command *cmd,
	t_parse_mask_str *new,
	int j,
	int index
)
{
	if (!(cmd->argv[index][0] == '$'))
	{
		while (cmd->argv[index][j] != '$')
		{
			new->str[j] = cmd->argv[index][j];
			new->mask[j] = cmd->masks[index][j];
			j++;
		}
	}
	return (j);
}

int	ft_cpy_before_dollard_file(
	t_redirection_list *buff,
	t_parse_mask_str *new, int j
)
{
	if (!(buff->redirection_file[0] == '$'))
	{
		while (buff->redirection_file[j] != '$')
		{
			new->str[j] = buff->redirection_file[j];
			new->mask[j] = buff->mask[j];
			j++;
		}
	}
	return (j);
}
