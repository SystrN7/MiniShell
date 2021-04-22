/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:57:33 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/22 14:36:53 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utilities.h"
#include "minishell_error.h"

int	commands_clear(t_node_binary *node)
{
	if (node == NULL)
		return (SUCCESS);
	commands_clear(node->left);
	commands_clear(node->right);
	node_clear(node);
	node->left = NULL;
	node->right = NULL;
	node->value = NULL;
	ft_managed_free(node);
	return (SUCCESS);
}

int	node_clear(t_node_binary *node)
{
	char	node_type;

	node_type = get_node_type(node);
	if (node_type == SHELL_INSTRUCTION_COMMAND)
		node_command_clear(node->value);
	ft_managed_free(node->value);
	return (SUCCESS);
}
