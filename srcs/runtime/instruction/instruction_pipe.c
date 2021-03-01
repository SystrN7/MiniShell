/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:41:47 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/01 16:56:14 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"

int		instruction_pipe(t_shell_context *context, t_node_binary *node)
{
	int		process_io[2];
	pid_t	pid;

	pipe(&process_io);

	if (pid < 0)
		error_occurs("fork do not work");
	else if (pid == 0)
	{
		
		close(standard_input);
	}
	else
	{
		
		close(standard_output);
	}
}
