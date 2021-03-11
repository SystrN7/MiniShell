/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:40:28 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/11 15:23:03 by fgalaup          ###   ########lyon.fr   */
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
};

static const struct		s_error_messages
{
	int					code;
	char				*message;
} error_messages[] = {
	{ERROR_UNDIFINED, "Undifined error (Just take a cooffe ☕)."},
	{ERROR_STD, "Is not an error for my bro."},
	{ERROR_ARG_TOO_MANY, "too many arguments"},
	{ERROR_ARG_REQUIRE_NUMERIC, "numeric argument required"},
	{ERROR_ENV_INVALID_IDENTIFIER, "not a valid identifier"},
	{0, NULL}
};

char	*error_get_message(int error_code);

int		error_message(t_shell_context *cnt, int code, int ret, char *emit);
int		error_fatal(t_shell_context *cnt, int code, int ret, char *emit);

// - ??? To remove
int		error_occure(char *error);

#endif
