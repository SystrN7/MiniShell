/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:11:11 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/03 17:20:44 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_scheduler.h"

enum
{
	IS_SORT,
	BRANCH_END,
	ERROR,
};

t_node_binary	*scheduler(t_shell_context *context, t_node_binary *unschedule_root)
{
	t_node_binary	**schedule_root;
	t_list			*priority_list;

	if (*((char *)unschedule_root->value) == SHELL_INSTRUCTION_COMMAND)
		return (unschedule_root);
	if (consistency_analyzer(context, unschedule_root))
		return (NULL);
	schedule_root = &unschedule_root;
	priority_list = scheduler_get_priority_list();
	schedule(priority_list, schedule_root, *schedule_root);
	ft_lstclear(&priority_list, free);
	binnary_show(*schedule_root, 4, "root");
	printf("\n");
	show_command(*schedule_root, 0);
	printf("\n");
	return (*schedule_root);
}

int	schedule(
	t_list	*priority,
	t_bnode **current_root,
	t_bnode *previous_node
)
{
	t_node_binary	*save_previous_node;
	t_node_binary	*current_node;

	ft_printf("cr:%p-cra:%p-pn:%p\n", current_root, *current_root, previous_node);
	while (previous_node && is_in_priority(priority->content, previous_node))
	{
		current_root = &previous_node->left;
		previous_node = previous_node->left;
		ft_printf("TsTed 4\n");
	}
	ft_printf("cr:%p-cra:%p-pn:%p\n", current_root, *current_root, previous_node);
	if (get_node_type(previous_node) == SHELL_INSTRUCTION_COMMAND)
		return (BRANCH_END);
	save_previous_node = previous_node;
	current_node = previous_node->left;
	while (current_node)
	{
		if (get_node_type(previous_node) == SHELL_INSTRUCTION_COMMAND)
		{
			if (priority->next == NULL)
				return (BRANCH_END);
			priority = priority->next;
			previous_node = save_previous_node;
			ft_printf("TsTed 1\n");
		}
		else if (is_in_priority(priority->content, previous_node))
		{
			ft_printf("cr:%p-cra:%p-cn:%p-pn:%p\n", current_root, *current_root, current_node, previous_node);
			schedule_swap(current_root, current_node, previous_node);
			ft_printf("TsTed 2\n");
			ft_printf("cr:%p-cra:%p-cn:%p-pn:%p\n", current_root, *current_root, current_node, previous_node);
			exit (0);
			schedule(priority, &current_node->left, current_node);
			schedule(priority, &current_node->right, current_node);
			return (IS_SORT);
		}
		ft_printf("TsTed 3\n");
		current_node = previous_node;
		previous_node = previous_node->left;
	}
	return (BRANCH_END);
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

t_bool	is_in_priority(char *priority, t_node_binary *node)
{
	char	node_type;
	size_t	i;		

	i = 0;
	node_type = get_node_type(node);
	while (priority[i])
	{
		if (priority[i] == node_type)
			return (TRUE);
		i++;
	}
	return (FALSE);
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
