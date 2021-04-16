/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:48:47 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/16 14:23:03 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_prompt.h"
#include "minishell_parser.h"
#include "minishell_scheduler.h"
#include "minishell_runtime.h"

int	prompt_file(t_shell_context *context)
{
	char			*line;
	t_node_binary	*root;
	t_node_binary	*schedule_root;
	int				read_status;

	context->line_number = 0;
	while (0 == 0)
	{
		read_status = get_next_line(standard_input, &line);
		context->line_number++;
		if (read_status == ERROR_STD)
			return (error_std(context, 1, NULL));
		root = ft_treat_line(line);
		ft_managed_free(line);
		schedule_root = scheduler(context, root);
		if (schedule_root != NULL)
		{
			run_instruction(context, schedule_root);
			commands_clear(schedule_root);
		}
		else
			commands_clear(root);
		if (read_status == 0)
			break ;
	}
	return (SUCCESS);
}
