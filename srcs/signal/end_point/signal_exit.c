/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:17:01 by felix             #+#    #+#             */
/*   Updated: 2021/04/15 12:06:56 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_signal.h"
#include "minishell_builtin.h"

void	signal_exit(int signal)
{
	t_shell_context	*context;
	char			*args[2];

	(void)signal;
	context = shell_get_context(NULL);
	args[path] = BUILTIN_EXIT;
	args[arg1] = NULL;
	builtin_exit(context, 1, args);
}
