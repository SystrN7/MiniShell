/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:11:11 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/03 11:24:18 by fgalaup          ###   ########lyon.fr   */
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
	schedule_separator(schedule_root, *schedule_root);
	binnary_show(*schedule_root, 4, "root");
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

	printf("Plop-\n");
	recution_state = schedule_separator(current_root, previous_node);
	printf("TEST-%d\n", recution_state);
	if (recution_state == IS_SORT)
	{
		printf("TEST-TEST\n");
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
	t_bool			is_junction;

	is_junction = FALSE;
	if (get_node_type(previous_node) == SHELL_SEPARATOR_TYPE_END)
		previous_node = previous_node->left;
	current_node = previous_node->left;
	while (current_node != NULL)
	{
		if (get_node_type(current_node) == SHELL_INSTRUCTION_COMMAND)
			return (IS_SORT);
		if (get_node_type(current_node) == SHELL_SEPARATOR_TYPE_END)
		{
			schedule_swap(current_root, current_node, previous_node);
			is_junction = TRUE;
			break ;
		}
		previous_node = current_node;
		current_node = current_node->left;
	}
	if (is_junction)
	{
		schedule(&current_node->left, current_node);
		schedule(&current_node->right, current_node);
		return (SORTED);
	}
	return (SORT);
}

int	schedule_or_and(
	t_bnode **current_root,
	t_bnode *previous_node
)
{
	t_node_binary	*current_node;
	t_bool			is_junction;

	is_junction = FALSE;
	if (get_node_type(previous_node) == SHELL_SEPARATOR_TYPE_OR
		&& get_node_type(previous_node) == SHELL_SEPARATOR_TYPE_AND)
		previous_node = previous_node->left;
	current_node = previous_node->left;
	while (current_node != NULL)
	{
		if (get_node_type(current_node) == SHELL_INSTRUCTION_COMMAND)
			return (IS_SORT);
		if (get_node_type(current_node) == SHELL_SEPARATOR_TYPE_OR
			|| get_node_type(previous_node) == SHELL_SEPARATOR_TYPE_AND)
		{
			schedule_swap(current_root, current_node, previous_node);
			is_junction = TRUE;
			break ;
		}
		previous_node = current_node;
		current_node = current_node->left;
	}
	if (is_junction)
	{
		schedule(&current_node->left, current_node);
		schedule(&current_node->right, current_node);
		return (SORTED);
	}
	return (SORT);
}

// int	schedule_separator(
// 	int deep,
// 	t_bnode **current_root,
// 	t_bnode *previous_node
// )
// {
// 	t_node_binary	*current_node;

// 	current_node = previous_node->left;
// 	if (*((char *)current_node->value) == SHELL_INSTRUCTION_COMMAND)
// 		return (IS_SORT);
// 	if (*((char *)current_node->value) == SHELL_SEPARATOR_TYPE_END)
// 	{
// 		schedule_swap(current_root, current_node, previous_node);
// 		deep = 0;
// 	}
// 	else
// 		deep++;
// 	if (current_node->left != NULL)
// 	{
// 		schedule_separator(deep, &current_node->left, current_node);
// 		if (deep == 0)
// 			schedule_or_and(deep, &current_node->left, current_node);
// 	}
// 	if (current_node->right != NULL)
// 	{
// 		schedule_separator(deep, &current_node->right, current_node);
// 		if (deep == 0)
// 			schedule_or_and(deep, &current_node->right, current_node);
// 	}
// 	return (IS_SORT);
// }

// int	schedule_or_and(
// 	int deep,
// 	t_bnode **current_root,
// 	t_bnode *previous_node
// )
// {
// 	t_node_binary	*current_node;

// 	current_node = previous_node->left;
// 	if (*((char *)current_node->value) == SHELL_INSTRUCTION_COMMAND)
// 		return (IS_SORT);
// 	if (*((char *)current_node->value) == SHELL_SEPARATOR_TYPE_AND
// 		|| *((char *)current_node->value) == SHELL_SEPARATOR_TYPE_OR)
// 	{
// 		schedule_swap(current_root, current_node, previous_node);
// 		deep = 0;
// 	}
// 	else
// 		deep++;
// 	if (current_node->left != NULL)
// 	{
// 		schedule_or_and(deep, &current_node->left, current_node);
// 		// if (deep == 0)
// 			// schedule_pipe(deep, &current_node->left, current_node);
// 	}
// 	if (current_node->right != NULL)
// 	{
// 		schedule_or_and(deep, &current_node->right, current_node);
// 		// schedule_pipe(deep, &current_node->right, current_node);
// 	}
// 	return (IS_SORT);
// }

void	schedule_swap(
	t_bnode **current_root,
	t_bnode *current_node,
	t_bnode *previous_node
)
{
	previous_node->left = current_node->right;
	current_node->right = *current_root;
	*current_root = current_node;
}
