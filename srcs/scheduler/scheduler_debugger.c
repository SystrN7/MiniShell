/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_debugger.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:00:01 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/27 14:01:49 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_scheduler.h"

void	show_node_value(t_node_binary *node)
{
	char				node_type;
	int					i;
	t_redirection_list	*it;
	t_shell_command		*command;

	node_type = get_node_type(node);
	if (node_type == SHELL_INSTRUCTION_COMMAND)
	{
		command = (t_shell_command *)node->value;
		i = 0;
		while (command->argv[i])
			ft_printf("%s ", (command->argv[i++]));
		it = command->redirection;
		while (it)
		{
			ft_printf("%s ", token_separator_get_string(it->redirection_type));
			ft_printf("%s ", it->redirection_file);
			it = it->next;
		}
	}
	else
		ft_printf("%s ", token_separator_get_string(node_type));
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
	show_node_value(root);
	binnary_show(root->left, space, "Left");
}

void	show_command(t_bnode *root, int deep)
{
	if (root->left)
		show_command(root->left, deep + 1);
	show_node_value(root);
	if (root->right)
		show_command(root->right, deep + 1);
}
