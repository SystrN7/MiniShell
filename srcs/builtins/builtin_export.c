/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 11:06:35 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/10 15:43:12 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
** |============================== EXPORT SPECS ===============================|
** Withous params is show all enviroment vars formated
** (declare -x VAR_NAME="VALUE")\n.
** If var is allready define with VAR_NAME=VALUE is move in enviromenent vars.
** Change of PWD OLDPWD dosent affect current shell location
** Exported var is affect if ther value as change
*/

#include "minishell_builtin.h"

int	builtin_export(t_shell_context *context, int argc, char **args)
{
	t_list	*list;

	if (argc == 1)
		builtin_export_print(context);
	else
		builtin_export_var(context, args);
	return (context->last_command_return_code);
}

void	builtin_export_var(t_shell_context *context, char **args)
{
	t_associative	env;
	int				i;

	i = 1;
	while (args[i])
	{
		if (env_is_identifier(args[i]))
		{
			env = env_key_value_split(args[i]);
			ft_lst_associative_set(
				&context->shared_environment,
				env.key,
				env.value
			);
		}
		else
			error_message(context, ERROR_ENV_INVALID_IDENTIFIER, 1, args[0]);
			ft_printf_fd(
				standard_error,
				"%s: export: `%s': not a valid identifier\n",
				context->shell_name,
				args[i]
			);
		i++;
	}
}

void	builtin_export_print(t_shell_context *context)
{
	t_list			*it;
	t_associative	*var;

	it = context->shared_environment;
	while (it)
	{
		var = (t_associative*)it->content;
		if (var->value == NULL)
			ft_printf("declare -x %s=\n", var->key);
		else
			ft_printf("declare -x %s=\"%s\"\n", var->key, var->value);
		it = it->next;
	}
}
