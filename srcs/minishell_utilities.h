/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utilities.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:33:31 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/08 17:11:28 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_UTILITIES_H
# define MINISHELL_UTILITIES_H

# include "libft.h"

# include "minishell_type.h"

# ifdef __APPLE__
#  include <sys/syslimits.h>
# elif __linux__
#  include <limits.h>
# endif

/**
 * =============================================================================
 *									  Console										
 * =============================================================================
 **/

void	console_clear(void);
void	console_prompt(t_shell_context *context);

/**
 * =============================================================================
 *									Environement
 * =============================================================================
 **/

t_list	*env_store(char *env[]);
t_asso	env_key_value_split(char *env_row);
char	*env_destore(t_associative *env);
char	**env_destore_all(t_list *env_list);
void	*env_get(t_shell_context *context, const char *key);
void	env_set(t_shell_context *context, char *key, char *value);

t_bool	env_is_assignment(const char *value);
t_bool	env_is_identifier(const char *value);

/**
 * =============================================================================
 *										Path
 * =============================================================================
 **/

char	*path_get_binary_path(char *env_path, char *binary_name);
t_bool	path_find_binary(char *directory_name, char *binary_name);

/**
 * =============================================================================
 *									   File
 * =============================================================================
 **/

t_bool	is_command(const char *path);

/**
 * ============================================================================
 *								Node & Binary Tree
 * ============================================================================
 **/

char	get_node_type(t_node_binary *node);
int		commands_clear(t_node_binary *node);
int		node_clear(t_node_binary *node);
int		node_command_clear(t_shell_command *command);
int		node_command_redirections_clear(t_redirection_list *redirections);

#endif
