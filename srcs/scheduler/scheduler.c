/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:11:11 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/09 14:56:36 by fgalaup          ###   ########lyon.fr   */
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

t_node_binary	*scheduler(
	t_shell_context *context,
	t_node_binary *unschedule_root
)
{
	t_node_binary	**schedule_root;

	if (get_node_type(unschedule_root) == SHELL_INSTRUCTION_COMMAND)
		return (unschedule_root);
	ft_printf("----------------------DEBUG----------------------\n");
	binnary_show(unschedule_root, 0, "Root");
	printf("\n");
	ft_printf("\n\nPost Sheduling command:`");
	show_command(unschedule_root, 0);
	ft_printf("`\n-------------------------------------------------\n");
	if (consistency_analyzer(context, unschedule_root))
		return (NULL);
	schedule_root = &unschedule_root;
	schedule(context->token, schedule_root, *schedule_root);
	return (*schedule_root);
}

int	schedule(
	t_list	*priority,
	t_bnode **current_root,
	t_bnode *previous_node
)
{
	int		recution_state;

	recution_state = schedule_separator(priority, current_root, previous_node);
	if (recution_state == IS_SORT)
	{
		priority = priority->next;
		if (priority != NULL)
			schedule_separator(priority, current_root, previous_node);
		return (SORTED);
	}
	return (SORT);
}

int	schedule_separator(
	t_list	*priority,
	t_bnode **current_root,
	t_bnode *previous_node
)
{
	t_node_binary	*current_node;
	t_node_binary	**working_root;

	working_root = current_root;
	while (is_in_priority(priority->content, previous_node))
	{
		working_root = &previous_node->left;
		previous_node = previous_node->left;
	}
	current_node = previous_node->left;
	while (current_node != NULL)
	{
		if (get_node_type(current_node) == SHELL_INSTRUCTION_COMMAND)
			return (IS_SORT);
		if (is_in_priority(priority->content, current_node))
		{
			schedule_swap(working_root, current_node, previous_node);
			schedule(priority, &current_node->left, current_node);
			schedule(priority, &current_node->right, current_node->right);
			return (SORTED);
		}
		previous_node = current_node;
		current_node = current_node->left;
	}
	return (IS_SORT);
}

t_list	*scheduler_get_priority_list(void)
{
	t_list	*priority_list;
	char	*id_separator;
	char	*ids_or_and;

	priority_list = NULL;
	id_separator = ft_calloc(sizeof(char), (1 + 1));
	ids_or_and = ft_calloc(sizeof(char), (2 + 1));
	id_separator[0] = (char)SHELL_SEPARATOR_TYPE_END;
	ids_or_and[0] = (char)SHELL_SEPARATOR_TYPE_AND;
	ids_or_and[1] = (char)SHELL_SEPARATOR_TYPE_OR;
	ft_lstnew_back(&priority_list, id_separator, free);
	ft_lstnew_back(&priority_list, ids_or_and, free);
	return (priority_list);
}

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
