/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 09:53:40 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/26 16:33:40 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtin.h"
#include "minishell_runtime.h"

int	builtin_env(t_shell_context *context, int argc, char **argv)
{
	t_list			*it;
	t_associative	*var;

	(void)argc;
	(void)argv;
	it = context->shared_environment;
	while (it)
	{
		var = (t_associative *)it->content;
		if (var->value != NULL && ft_strlen(var->value))
			ft_printf("%s=%s\n", var->key, var->value);
		it = it->next;
	}
	return (context->last_command_return_code);
}
