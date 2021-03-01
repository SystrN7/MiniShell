/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:11:11 by fgalaup           #+#    #+#             */
/*   Updated: 2021/02/08 11:24:43 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_scheduler.h"

int		scheduler(t_shell_context *context, t_list **command_list)
{
	t_list			*it;
	t_node_binary	*root;

	root = NULL;
	it = *command_list;
	scheduler_recursive(&it, );
	ft_lstclear(command_list, NULL);
	return (SUCCESS);
}

int		scheduler_recursive(t_list **it, t_node_binary *current_node)
{
	*it = ((t_list *)*it)->next;
	scheduler_recursive(it, );
	return (SUCCESS);
}

int		schedule_command(t_shell_command *cmd, t_node_binary **current_node)
{
	if (((char)**current_node->value) == SHELL_INSTRUCTION_COMMAND)
	{
		
	}
	else
	{
		/* code */
	}
	return (SUCCESS);
}

int		schedule_separator(t_shell_separator *separator, t_node_binary **current_node)
{
	if (((char)**current_node->value) == SHELL_INSTRUCTION_PIPE)
	{

	}
	else
	{

	}
	return (SUCCESS);
}


// int		scheduler(t_shell_context *context, t_list **command_list)
// {
// 	t_list			*it;
// 	t_node_binary	*root;
// 	t_node_binary	*current_node;

// 	root = NULL;
// 	current_node = NULL;
// 	it = *command_list;
// 	while (it)
// 	{
// 		if (root == NULL)
// 			root = current_node;
// 		schedule_instruction(it->content, current_node);

// 		it = it->next;
// 	}
// 	ft_lstclear(command_list, NULL)
// 	return (0);
// }

// int		schedule_instruction(void *instruction, t_node_binary *current_node)
// {
// 	if (((char)*it->content) == SHELL_INSTRUCTION_COMMAND)
// 		schedule_command(it->content);
// 	else if (((char)*it->content) == SHELL_INSTRUCTION_SEPARATOR)
// 		schedule_separator(it->content);
// 	else
// 		return (ERROR_UNKNOWN_INSTRUCTION_TYPE);
// }
