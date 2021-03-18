/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:40:28 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/17 14:15:49 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ERROR_H
# define MINISHELL_ERROR_H

# include <errno.h>
# include <string.h>
# include <stdio.h>

# include "libft.h"

# include "minishell.h"
# include "minishell_type.h"

enum					e_error_code
{
	ERROR_STD = -1,
	SUCCESS = 0,
	ERROR_MALLOC,
	ERROR_UNDIFINED,
	ERROR_ARG_TOO_MANY,
	ERROR_ARG_REQUIRE_NUMERIC,
	ERROR_ENV_INVALID_IDENTIFIER,
	ERROR_RUNTIME_UNKNOWN_INSTRUCTION,
	ERROR_RUNTIME_UNKNOWN_COMMAND,
	ERROR_SYNTAX_INVALID_INSTRUCTION,
	ERROR_SYNTAX_COMMAND_NOT_END,
	ERROR_BUILTIN_CD_NO_VAR,
};

static const struct		s_error_messages
{
	int					code;
	char				*message;
} error_messages[] = {
	{ERROR_UNDIFINED, "Undifined error (Just take a cooffe ☕)."},
	{ERROR_STD, "%s: Is not an error for my bro."},
	{ERROR_ARG_TOO_MANY, "%s: too many arguments"},
	{ERROR_ARG_REQUIRE_NUMERIC, "%s: numeric argument required"},
	{ERROR_ENV_INVALID_IDENTIFIER, "%s: `%s': not a valid identifier"},
	{ERROR_RUNTIME_UNKNOWN_INSTRUCTION, "unknown instruction is found"},
	{ERROR_RUNTIME_UNKNOWN_COMMAND, "%s: command not found"},
	{ERROR_SYNTAX_INVALID_INSTRUCTION, "`%d': is invalid instruction code"},
	{ERROR_SYNTAX_COMMAND_NOT_END, "command is not the end"},
	{ERROR_BUILTIN_CD_NO_VAR, "%s: %s not set"},
	{0, NULL}
};

char	*error_get_message(int error_code);
int		error_print_messages(t_shell_context *cnt, int ec, int rc, va_list arg);

int		error_message(t_shell_context *context, int error_code, int retc, ...);
int		error_fatal(t_shell_context *context, int error_code, int retc, ...);
int		error_builtin(t_shell_context *context, int error_code, int retc, ...);

#endif
