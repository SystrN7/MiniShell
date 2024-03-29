/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:52:37 by felix             #+#    #+#             */
/*   Updated: 2021/04/15 11:52:20 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SIGNAL_H
# define MINISHELL_SIGNAL_H

# include <signal.h>

# include "minishell.h"
# include "minishell_type.h"

int		signal_register(t_shell_context *context);

void	signal_do_nothing(int signal);
void	signal_new_prompt(int signal);
void	signal_exit(int signal);

#endif