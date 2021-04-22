/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 14:27:14 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/22 10:26:12 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_scheduler.h"
#include "minishell_utilities.h"
#include "minishell_prompt.h"

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
	context->token = scheduler_get_priority_list();
	context->token_separator = token_separator_get_list();
	context->standard_input_backup = dup(standard_input);
	context->standard_output_backup = dup(standard_output);
	context->interactive_mode = FALSE;
	context->line_number = 0;
	context->shell_name = (char *)argv[path];
	env_set(context, "OLDPWD", NULL);
	env_set(context, "PWD", getcwd(ft_managed_malloc(PATH_MAX), PATH_MAX));
}

void	shell_start(char const *argv[], char *env[])
{
	t_shell_context	*context;

	context = ft_managed_malloc(sizeof(t_shell_context));
	shell_init(context, argv, env);
	prompt(context, argv);
	shell_shutdown(context);
}

void	shell_shutdown(t_shell_context *context)
{
	unsigned char	return_code;

	ft_managed_free(context->token_separator);
	ft_lstclear(&context->token, &ft_managed_free);
	ft_lstclear(&context->local_environement, &ft_lst_associative_del_free);
	ft_lstclear(&context->shared_environment, &ft_lst_associative_del_free);
	ft_managed_free(context->shell_name);
	ft_managed_free(context->line);
	close(context->standard_input_backup);
	close(context->standard_output_backup);
	return_code = context->last_command_return_code % 256;
	ft_managed_free(context);
	ft_managed_free_all();
	exit(return_code);
}
