/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_and.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:20:51 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/06 11:22:37 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"

int	instruction_and(t_shell_context *context, t_node_binary *node)
{
	if (run_instruction(context, node->left) == 0)
		run_instruction(context, node->right);
	return (context->last_command_return_code);
}
