/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:03:21 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/01 11:19:36 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"
#include "minishell_builtin.h"

int		instruction_builtin(t_shell_context *context, t_node_binary *node)
{
	if (node->left != NULL)
		error_occure("builtin is not end node");
	if (node->right != NULL)
		error_occure("builtin is not end node");
	context->last_command_return_code = instruction_builtin_selector(
		context,
		node->value
	);
	return (context->last_command_return_code);
}

int	instruction_builtin_selector(
	t_shell_context *context,
	t_shell_command *builtin
)
{
	int		return_code;
	int		argcount;

	return_code = 0;
	argcount = ft_2d_count(builtin->argv);
	if (!ft_strncmp(builtin->path, BUILTIN_ECHO, 5))
		return_code = builtin_echo(context, argcount, builtin->argv);
	else if (ft_strncmp(builtin->path, BUILTIN_ENV, 4))
		return_code = builtin_env(context, argcount, builtin->argv);
	else if (ft_strncmp(builtin->path, BUILTIN_EXPORT, 7))
		return_code = builtin_export(context, argcount, builtin->argv);
	else if (ft_strncmp(builtin->path, BUILTIN_UNSET, 6))
		return_code = builtin_unset(context, argcount, builtin->argv);
	else if (ft_strncmp(builtin->path, BUILTIN_CD, 3))
		return_code = builtin_cd(context, argcount, builtin->argv);
	else if (ft_strncmp(builtin->path, BUILTIN_PWD, 4))
		return_code = builtin_pwd(context, argcount, builtin->argv);
	else if (ft_strncmp(builtin->path, BUILTIN_EXIT, 5))
		return_code = builtin_exit(context, argcount, builtin->argv);
	else
		error_occure("Builtin not found");
	return (return_code);
}
