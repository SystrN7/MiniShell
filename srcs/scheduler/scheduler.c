/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:11:11 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/04 14:53:31 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_scheduler.h"

enum
{
	SORTED,
	IS_SORT,
	SORT,
	ERROR,
};

t_node_binary	*scheduler(t_shell_context *context, t_node_binary *unschedule_root)
{
	t_node_binary	**schedule_root;

	if (*((char *)unschedule_root->value) == SHELL_INSTRUCTION_COMMAND)
		return (unschedule_root);
	if (consistency_analyzer(context, unschedule_root))
		return (NULL);
	schedule_root = &unschedule_root;
	binnary_show(*schedule_root, 4, "Root");
	printf("\n");
	schedule(schedule_root, *schedule_root);
	binnary_show(*schedule_root, 4, "Root");
	printf("\n");
	show_command(*schedule_root, 0);
	printf("\n");
	return (*schedule_root);
}

int	schedule(
	t_bnode **current_root,
	t_bnode *previous_node
)
{
	int		recution_state;

	recution_state = schedule_separator(current_root, previous_node);
	if (recution_state == IS_SORT)
	{
		recution_state = schedule_or_and(current_root, previous_node);
		if (recution_state == IS_SORT)
			return (SORTED);
	}
	return (SORT);
}

int	schedule_separator(
	t_bnode **current_root,
	t_bnode *previous_node
)
{
	t_node_binary	*current_node;
	t_node_binary	**working_root;

	working_root = current_root;
	while (get_node_type(previous_node) == SHELL_SEPARATOR_TYPE_END)
	{
		working_root = &previous_node->left;
		previous_node = previous_node->left;
	}
	current_node = previous_node->left;
	while (current_node != NULL)
	{
		if (get_node_type(current_node) == SHELL_INSTRUCTION_COMMAND)
			return (IS_SORT);
		if (get_node_type(current_node) == SHELL_SEPARATOR_TYPE_END)
		{
			schedule_swap(working_root, current_node, previous_node);
			schedule(&current_node->left, current_node);
			schedule(&current_node->right, current_node);
			return (SORTED);
		}
		previous_node = current_node;
		current_node = current_node->left;
	}
	return (IS_SORT);
}

int	schedule_or_and(
	t_bnode **current_root,
	t_bnode *previous_node
)
{
	t_node_binary	*current_node;
	t_node_binary	**working_root;

	working_root = current_root;
	current_node = previous_node;
	while (get_node_type(current_node) == SHELL_SEPARATOR_TYPE_OR
		|| get_node_type(current_node) == SHELL_SEPARATOR_TYPE_AND)
	{
		ft_printf("ke le pls \n");
		working_root = &current_node->left;
		previous_node = current_node;
		current_node = current_node->left;
	}
	ft_printf("befor swap :\n - previous node = %s\n - current node =%s\n - current root=%s\n\n",
		node_get_value(previous_node),
		node_get_value(previous_node->left),
		node_get_value(*current_root)
	);
	while (current_node != NULL)
	{
		if (get_node_type(current_node) == SHELL_INSTRUCTION_COMMAND)
			return (IS_SORT);
		if ((get_node_type(current_node) == SHELL_SEPARATOR_TYPE_OR
				|| get_node_type(current_node) == SHELL_SEPARATOR_TYPE_AND)
			&& get_node_type(previous_node) != SHELL_SEPARATOR_TYPE_END)
		{
			schedule_swap(working_root, current_node, previous_node);
			schedule(&current_node->left, current_node);
			schedule(&current_node->right, current_node);
			return (SORTED);
		}
		previous_node = current_node;
		current_node = current_node->left;
	}
	return (IS_SORT);
}

void	schedule_swap(
	t_bnode **current_root,
	t_bnode *current_node,
	t_bnode *previous_node
)
{
	ft_printf("Swap :\n - previous node = %s\n - current node =%s\n - current root=%s\n\n",
		node_get_value(previous_node),
		node_get_value(current_node),
		node_get_value(*current_root)
	);
	previous_node->left = current_node->right;
	current_node->right = *current_root;
	*current_root = current_node;
}