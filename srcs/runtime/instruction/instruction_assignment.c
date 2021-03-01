/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_assignment.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:52:24 by fgalaup           #+#    #+#             */
/*   Updated: 2021/02/20 14:42:46 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"

int		instruction_assignment(t_shell_context *context, t_node_binary *node)
{
	// node->left name of variable
	if (*((char*)(node->right->value)) == SHELL_STRING)
		env
	return (0);
}
