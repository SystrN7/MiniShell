/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_debugger.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:00:01 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/09 14:53:39 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_scheduler.h"

char	*node_get_value(t_node_binary *node)
{
	char	node_type;

	node_type = get_node_type(node);
	if (node_type == SHELL_INSTRUCTION_COMMAND)
		return (ft_2d_merge(((t_shell_command *)node->value)->argv));
	else
	{
		if (node_type == SHELL_SEPARATOR_TYPE_AND)
			return ("&&");
		else if (node_type == SHELL_SEPARATOR_TYPE_OR)
			return ("||");
		else if (node_type == SHELL_SEPARATOR_TYPE_END)
			return (";");
		else if (node_type == SHELL_SEPARATOR_TYPE_PIPE)
			return ("|");
		else
			return ("?");
	}
	return (NULL);
}

void	binnary_show(t_bnode *root, int space, char *side)
{
	int	i;

	if (root == NULL)
		return ;
	space += 4;
	binnary_show(root->right, space, "Right");
	ft_printf("\n");
	i = 4;
	while (i++ < space)
		ft_printf(" ");
	ft_printf("%s:", side);
	ft_printf("(%s)", node_get_value(root));
	binnary_show(root->left, space, "Left");
}

void	show_command(t_bnode *root, int deep)
{
	if (root->left)
		show_command(root->left, deep + 1);
	ft_printf("%s", node_get_value(root));
	if (root->right)
		show_command(root->right, deep + 1);
}
