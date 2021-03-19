/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felix <felix@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 14:27:14 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/19 10:11:03 by felix            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_builtin.h"
#include "minishell_parser.h"
#include "minishell_runtime.h"
#include "minishell_utilities.h"

int	main(int argc, char const *argv[], char *env[])
{
	(void)argc;
	shell_start(argv, env);
	return (0);
}

void	shell_init(t_shell_context *context, char const *argv[], char *env[])
{
	ft_memset(context, 0, sizeof(t_shell_context));
	context->shared_environment = env_store(env);
	ft_managed_termination_function((t_term)shell_shutdown);
	ft_managed_termination_params(context);
	context->standard_input_backup = dup(standard_input);
	context->standard_output_backup = dup(standard_output);
	context->shell_name = ft_strsplit_last(argv[path], '/');
}

void	shell_start(char const *argv[], char *env[])
{
	t_shell_context	context;
	char			*line;
	t_node_binary	*root;

	(void)argv;
	shell_init(&context, argv, env);
	console_clear();
	console_prompt(&context);
	while (get_next_line(0, &line) >= 0)
	{
		root = ft_treat_line(line);
		run_instruction(&context, root);
		ft_managed_free(line);
		console_prompt(&context);
	}
	shell_shutdown(&context);
}

void	shell_shutdown(t_shell_context *context)
{
	unsigned char	return_code;

	ft_managed_free_all();
	return_code = context->last_command_return_code % 256;
	exit(return_code);
}
