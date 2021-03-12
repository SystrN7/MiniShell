/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:13:21 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/11 16:18:44 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include "minishell_type.h"
# include "minishell_error.h"
# include "minishell_utilities.h"

void	shell_init(t_shell_context *context, char const *argv[], char *env[]);
void	shell_start(char const *argv[], char *env[]);
void	shell_shutdown(t_shell_context *context);

#endif
