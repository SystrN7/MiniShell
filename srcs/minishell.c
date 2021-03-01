/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 14:27:14 by fgalaup           #+#    #+#             */
/*   Updated: 2021/02/18 12:46:23 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// To Remove
#include "minishell_test.h"

/*
** Main Function of minishellmake
*/

int		main(int argc, char const *argv[], char *env[])
{
	(void)argc;
	shell_start(argv, env);
	return (0);
}

void	shell_init(t_shell_context *context, char *env[])
{
	ft_memset(context, 0, sizeof(t_shell_context));
	context->shared_environment = env_store(env);
}

void	shell_start(char const *argv[], char *env[])
{
	t_shell_context	context;

	(void)argv;
	shell_init(&context, env);
}

void	shell_shutdown(t_shell_context *context)
{
	unsigned char	return_code;

	ft_managed_free_all();
	return_code = context->last_command_return_code % 256;
	exit(return_code);
}

