/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:48:47 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/17 16:16:08 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_prompt.h"
#include "minishell_parser.h"
#include "minishell_scheduler.h"
#include "minishell_runtime.h"

int	prompt_command(t_shell_context *context, const char *command)
{
	t_node_binary	*root;
	t_node_binary	*schedule_root;

	context->line_number = 0;
	context->line = ft_strdup(command);
	root = ft_treat_line((char *)command);
	schedule_root = scheduler(context, root);
	if (schedule_root != NULL)
	{
		run_instruction(context, schedule_root);
		commands_clear(schedule_root);
	}
	else
		commands_clear(root);
	return (SUCCESS);
}
