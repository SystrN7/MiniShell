/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utilities.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:33:31 by fgalaup           #+#    #+#             */
/*   Updated: 2021/02/20 11:29:36 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_UTILITIES_H
# define MINISHELL_UTILITIES_H

# include "libft.h"

/*
** =============================================================================
**									  DEBUG
** =============================================================================
*/

void	debug_print_env(char *env[]);

/*
** =============================================================================
**									ENVIRONEMENT
** =============================================================================
*/

t_list	*env_store(char *env[]);
t_asso	env_key_value_split(char *env_row);
char	*env_destore(t_associative *env);
char	**env_destore_all(t_list *env_list);
void	*env_get(t_shell_context *context, char *key);

/*
** =============================================================================
**										PATH
** =============================================================================
*/

char	*path_get_binary_path(char *env_path, char *binary_name);
t_bool	path_find_binary(char *directory_name, char *binary_name);

#endif
