/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_type.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:19:16 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/09 12:17:51 by seruiz           ###   ########lyon.fr   */
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

	int		standard_input_backup;
	int		standard_output_backup;

	int		running_command_pid;
	int		last_command_return_code;
}				t_shell_context;

/*
** =============================================================================
**									Shell Instruction
** =============================================================================
*/

enum e_shell_instruction_type
{
	SHELL_INSTRUCTION_UNKNOWN = 'u',
	SHELL_INSTRUCTION_COMMAND = 'c',
	SHELL_SEPARATOR_TYPE_END = 'e',
	SHELL_SEPARATOR_TYPE_PIPE = 'p',
	SHELL_SEPARATOR_TYPE_AND = 'a',
	SHELL_SEPARATOR_TYPE_OR = 'o',
};

enum e_shell_redirection_type
{
	SHELL_REDIRECT_TYPE_LEFT,
	SHELL_REDIRECT_TYPE_RIGHT,
	SHELL_REDIRECT_TYPE_DOUBLE_LEFT,
	SHELL_REDIRECT_TYPE_DOUBLE_RIGHT,
};

enum e_shell_args
{
	path,
	arg1,
	arg2,
	arg3,
};

typedef struct s_shell_redirection
{
	char	type;
	char	*file_name;
	int		fd;
}				t_shell_redirection;

typedef struct s_redirection_list
{
	char						redirection_type;
	char						*redirection_file;
	char						*mask;
	int							fd;
	struct s_redirection_list	*next;
}				t_redirection_list;

typedef struct s_shell_command
{
	char				instruction_type;
	char				*command_string;
	char				*command_mask;
	char				*path;
	char				**argv;
	char				**masks;
	t_redirection_list	**redirection;
}				t_shell_command;

typedef struct s_shell_separator
{
	char	instruction_type;
}				t_shell_separator;


#endif
