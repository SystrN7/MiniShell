/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_tty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:09:01 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/21 14:48:23 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_prompt.h"
#include "minishell_parser.h"
#include "minishell_scheduler.h"
#include "minishell_runtime.h"
#include "minishell_utilities.h"
#include "minishell_signal.h"
#include "minishell_termcaps.h"

int	prompt_tty(t_shell_context *context)
{
	 if (prompt_tty_init(context))
		return (error_message(context, ERROR_STD, 1));
	return (prompt_tty_loop(context));
}

int	prompt_tty_init(t_shell_context *context)
{
	char	*name_backup;

	console_clear();
	name_backup = context->shell_name;
	context->shell_name = ft_strsplit_last(context->shell_name, '/');
	context->interactive_mode = FT_TRUE;
	ft_managed_free(name_backup);
	name_backup = NULL;
	return (signal_register(context));
}

int	prompt_tty_loop(t_shell_context *context)
{
	char					*line;
	t_node_binary			*root;
	t_node_binary			*schedule_root;
	t_bidirectional_list	*history;
	//int				read_status;

	history = NULL;
	//console_prompt(context);
	while (0 == 0)
	{
		//read_status = get_next_line(0, &line);
		line = terms_input_mode(context, history);
		context->line = line;
		//if (read_status == ERROR_STD)
		//	return (error_std(context, 1, NULL));
		ft_blst_new_front(&history, line, &ft_managed_free);
		root = ft_treat_line(line);
		//ft_managed_free(line);
		schedule_root = scheduler(context, root);
		if (schedule_root != NULL)
		{
			run_instruction(context, schedule_root);
			commands_clear(schedule_root);
		}
		else
			commands_clear(root);
		//console_prompt(context);
	}
	return (SUCCESS);
}
