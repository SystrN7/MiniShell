/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 12:39:41 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/27 16:19:48 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_prompt.h"

int	prompt(t_shell_context *context, const char *argv[])
{
	int		prompt_type;

	prompt_type = identify_prompt_type(argv);
	if (prompt_type == PROMPT_TYPE_COMMAND)
		return (prompt_command(context, argv[arg2]));
	else if (prompt_type == PROMPT_TYPE_FILE)
		return (prompt_file(context));
	else if (prompt_type == PROMPT_TYPE_TTY)
		return (prompt_tty(context));
	return (SUCCESS);
}

int	identify_prompt_type(const char *argv[])
{
	if (argv[arg1] && argv[arg1][0] == '-' && argv[arg1][1] == 'c')
		if (argv[arg2])
			return (PROMPT_TYPE_COMMAND);
	if (isatty(standard_input) && isatty(standard_output))
		return (PROMPT_TYPE_TTY);
	return (PROMPT_TYPE_FILE);
}
