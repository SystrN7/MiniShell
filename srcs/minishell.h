/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:13:21 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/21 11:35:40 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include "minishell_type.h"
# include "minishell_error.h"
# include "minishell_utilities.h"

typedef t_shell_context	t_scnt;

void	shell_init(t_shell_context *context, char const *argv[], char *env[]);
void	shell_start(char const *argv[], char *env[]);
void	shell_shutdown(t_shell_context *context);
t_scnt	*shell_get_context(t_shell_context *context);

#endif
