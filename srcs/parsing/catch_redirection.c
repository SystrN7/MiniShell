/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:53:04 by seruiz            #+#    #+#             */
/*   Updated: 2021/03/17 15:07:28 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"
#include "minishell_builtin.h"
#include "minishell_utilities.h"

#include <unistd.h>

int	ft_redirection_found(t_shell_command *cmd, int i)
{
	int	j;

	(void)cmd;
	(void)i;
	j = 0;
	return (j);
}

void	ft_catch_redirection(t_shell_context *context, t_shell_command *cmd)
{
	int	i;

	(void)context;
	i = 0;
	while (cmd->command_string[i])
	{
		if ((cmd->command_string[i] == '>' || cmd->command_string[i] == '<') && cmd->command_mask[i] == '0')
			i = ft_redirection_found(cmd, i);
		else
			i++;
	}
}