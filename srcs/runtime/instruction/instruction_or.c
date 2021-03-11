/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:20:53 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/11 15:26:13 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"

int		instruction_or(t_shell_context *context, t_node_binary *node)
{
	if (run_instruction(context, node->left) != 0)
		run_instruction(context, node->right);
	return (context->last_command_return_code);
}
