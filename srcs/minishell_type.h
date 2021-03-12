/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_type.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:19:16 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/12 10:23:03 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TYPE_H
# define MINISHELL_TYPE_H

# include "ft_type.h"

typedef struct s_shell_context
{
	char	*shell_name;

	t_list	*local_environement;
	t_list	*shared_environment;

	char	*path_current;
	char	*path_previous;

	int		last_command_return_code;
}				t_shell_context;

/*
** =============================================================================
**									Shell Instruction
** =============================================================================
*/

enum e_shell_instruction_type
{
	SHELL_INSTRUCTION_UNKNOWN,
	SHELL_INSTRUCTION_COMMAND,
	SHELL_SEPARATOR_TYPE_END,
	SHELL_SEPARATOR_TYPE_PIPE,
	SHELL_SEPARATOR_TYPE_AND,
	SHELL_SEPARATOR_TYPE_OR,
};

enum e_shell_redirection_type
{
	SHELL_SEPARATOR_TYPE_REDIRECT_LEFT,
	SHELL_SEPARATOR_TYPE_REDIRECT_RIGHT,
	SHELL_SEPARATOR_TYPE_REDIRECT_DOUBLE_LEFT,
	SHELL_SEPARATOR_TYPE_REDIRECT_DOUBLE_RIGHT,
};

enum e_shell_args
{
	path,
	arg1,
	arg2,
	arg3,
};

typedef struct s_shell_command
{
	char	instruction_type;
	char	*command_string;
	char	*command_mask;
	char	*path;
	char	**argv;
	char	redirection_type;
	char	*redirection_file;
}				t_shell_command;

typedef struct s_shell_separator
{
	char	instruction_type;
	int		type;
}				t_shell_separator;

#endif
