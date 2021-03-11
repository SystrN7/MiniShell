/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_runtime.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:53:12 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/11 15:17:49 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_RUNTIME_H
# define MINISHELL_RUNTIME_H

# include <fcntl.h>
# include <unistd.h>

# include "minishell_type.h"
# include "minishell_error.h"

// ===============================RUNTIME CORE=============================== //
int		run_instruction(t_shell_context *context, t_node_binary *node);
int		run_separator(t_shell_context *cnt, char n_type, t_node_binary *node);

// ===============================INSTRUCTION================================ //

// --------------------------------Utilities--------------------------------- //

int		instruction_builtin_selector(t_shell_context *cnt, t_shell_command *bi);
int		command_run(t_shell_context *context, t_shell_command *command);

// ---------------------------------Command---------------------------------- //

int		instruction_command(t_shell_context *context, t_node_binary *node);
int		instruction_builtin_exec(t_shell_context *context, t_shell_command *builtin);
int		instruction_command_exec(t_shell_context *context, t_shell_command *command);
char	*command_path_resolver(t_shell_context *context, t_shell_command *command);

// --------------------------------Separator--------------------------------- //
int		instruction_separator(t_shell_context *context, t_node_binary *node);
int		instruction_pipe(t_shell_context *context, t_node_binary *node);
int		instruction_and(t_shell_context *context, t_node_binary *node);
int		instruction_or(t_shell_context *context, t_node_binary *node);

#endif
