/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_prompt.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:17:48 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/15 16:03:57 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PROMPT_H
# define MINISHELL_PROMPT_H

# include <term.h>
// # include <curses.h>

# include "minishell_type.h"
# include "minishell_error.h"

enum e_prompt_type
{
	PROMPT_TYPE_COMMAND,
	PROMPT_TYPE_FILE,
	PROMPT_TYPE_TTY,
};

int		prompt(t_shell_context *context, const char *argv[]);
int		identify_prompt_type(const char *argv[]);

int		prompt_command(t_shell_context *context, const char *command);

int		prompt_file(t_shell_context *context);

int		prompt_tty(t_shell_context *context);
int		prompt_tty_init(t_shell_context *context);
int		prompt_tty_loop(t_shell_context *context);

#endif