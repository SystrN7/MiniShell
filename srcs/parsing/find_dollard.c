/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_dollard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:42:17 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/23 12:42:27 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"
#include "minishell_builtin.h"
#include "minishell_utilities.h"
#include "minishell_parser.h"

#include <unistd.h>

void	ft_treat_var(t_shell_context *context, t_shell_command *cmd)
{
	t_parse_pos	s;

	s.i = 0;
	s.index =0;
	while (cmd->argv[s.index])
	{
		while (cmd->argv[s.index][s.i])
		{
			if (cmd->argv[s.index][s.i] == '$' &&
					cmd->masks[s.index][s.i] != '1')
			{
				s.i++;
				s.i = ft_replace_var_argv(context, cmd, s);
			}
			else
				s.i++;
		}
		s.i = 0;
		s.index++;
	}
	ft_replace_filenames(context, cmd);
}
