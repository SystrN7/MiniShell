/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_type.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:19:16 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/26 15:16:12 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TYPE_H
# define MINISHELL_TYPE_H

# include "ft_type.h"

# include <limits.h>

typedef struct s_shell_context
{
	char	*shell_name;

	t_bool	interactive_mode;
	int		line_number;
	char	line_buff[2000];
	int		line_i;
	char	*line;

	t_list	*token;
	char	*token_separator;

	t_list	*local_environement;
	t_list	*shared_environment;

	int		standard_input_backup;
	int		standard_output_backup;
	int		standard_error_backup;

	int		last_command_return_code;
}				t_shell_context;

/*
** =============================================================================
**									Shell Instruction
** =============================================================================
*/

enum e_shell_instruction_type
{
	SHELL_INSTRUCTION_UNKNOWN = 1,
	SHELL_INSTRUCTION_COMMAND,
	SHELL_SEPARATOR_TYPE_END,
	SHELL_SEPARATOR_TYPE_PIPE,
	SHELL_SEPARATOR_TYPE_AND,
	SHELL_SEPARATOR_TYPE_OR,
	SHELL_REDIRECT_FILE,
	SHELL_REDIRECT_TYPE_LEFT,
	SHELL_REDIRECT_TYPE_RIGHT,
	SHELL_REDIRECT_TYPE_DOUBLE_LEFT,
	SHELL_REDIRECT_TYPE_DOUBLE_RIGHT,
	SHELL_END_LINE,
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
	int							source_fd;
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
	t_redirection_list	*redirection;
}				t_shell_command;

typedef struct s_shell_separator
{
	char	instruction_type;
}				t_shell_separator;

#endif
