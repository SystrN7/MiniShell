/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 14:27:14 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/04 16:50:30 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_builtin.h"
#include "minishell_parser.h"
#include "minishell_scheduler.h"
#include "minishell_runtime.h"
#include "minishell_utilities.h"


t_shell_context	*shell_get_context(t_shell_context *context)
{
	static t_shell_context	*save_context;

	if (context != NULL)
		save_context = context;
	return (save_context);
}


int	main(int argc, char const *argv[], char *env[])
{
	(void)argc;
	shell_start(argv, env);
	return (0);
}

void	shell_init(t_shell_context *context, char const *argv[], char *env[])
{
	ft_memset(context, 0, sizeof(t_shell_context));
	shell_get_context(context);
	context->shared_environment = env_store(env);
	ft_managed_termination_function((t_term)shell_shutdown);
	ft_managed_termination_params(context);
	context->standard_input_backup = dup(standard_input);
	context->standard_output_backup = dup(standard_output);
	context->shell_name = ft_strsplit_last(argv[path], '/');
}

void	signal_test_gnl(int num)
{
	t_shell_context	*context;

	context = shell_get_context(NULL);
	ft_putstr_fd(standard_output, "\b\b  \n");
	console_prompt(context);
	(void)num;

}

void	signal_print(int num)
{
	(void)num;
	printf("ctrl D found\n");
}

void	shell_start(char const *argv[], char *env[])
{
	t_shell_context	context;
	char			*line;
	t_node_binary	*root;

	signal(SIGINT, signal_test_gnl);
	(void)argv;
	shell_init(&context, argv, env);
	console_clear();
	console_prompt(&context);
	while (get_next_line(0, &line) >= 0)
	{
		root = ft_treat_line(line);
		scheduler(&context, root);
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
