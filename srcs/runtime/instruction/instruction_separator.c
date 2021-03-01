/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_separator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:49:44 by fgalaup           #+#    #+#             */
/*   Updated: 2021/02/20 14:33:24 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"

#include "minishell_type.h"

int		instruction_separator(t_shell_context *context, t_node_binary *node)
{
	run_instruction(context, node->left);
	run_instruction(context, node->right);
	return (context->last_command_return_code);
}
