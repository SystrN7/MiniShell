/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:11:11 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/28 16:35:50 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_scheduler.h"

enum
{
	SORT,
	IS_SORT,
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
	schedule_separator(0, schedule_root, *schedule_root);
	binnary_show(*schedule_root, 4, "root");
	show_command(*schedule_root, 0);
	printf("\n");
	return (*schedule_root);
}

// int	schedule(
// 	t_shell_context *context,
// 	t_bnode **current_root,
// 	t_bnode *previous_node
// )
// {
// 	if (schedule_separator(context, current_root, ) == SORT)
// 	// schedule_or_and(context, current_root);
// 	// schedule_pipe(context, current_root);
// }



// int	schedule_separator(
// 	t_shell_context *context,
// 	t_bnode **current_root,
// 	t_bnode *previous_node
// )
// {
// 	t_node_binary	*current_node;

// 	current_node = previous_node->left;
// 	while (current_node)
// 	{
// 		if (*((char *)current_node->value) == SHELL_INSTRUCTION_COMMAND)
// 			return (IS_SORT)
// 		if (*((char *)current_node->value) == SHELL_SEPARATOR_TYPE_END)
// 		{
// 			schedule_swap(current_root, current_node, previous_node);
// 			break ;
// 		}
// 		previous_node = current_node;
// 		current_node = previous_node->left;
// 	}
// 	if (current_node->left != NULL)
// 	{
// 		schedule_separator(context, &current_node->left, current_node);
// 		schedule_or_and(context, &current_node->left, current_node);
// 	}
// 	if (current_node->right != NULL)
// 	{
// 		schedule_separator(context, &current_node->right, current_node);
// 		schedule_or_and(context, &current_node->right, current_node);
// 	}
// 	return (IS_SORT);
// }

int	schedule_separator(
	int deep,
	t_bnode **current_root,
	t_bnode *previous_node
)
{
	t_node_binary	*current_node;

	current_node = previous_node->left;
	if (*((char *)current_node->value) == SHELL_INSTRUCTION_COMMAND)
		return (IS_SORT);
	if (*((char *)current_node->value) == SHELL_SEPARATOR_TYPE_END)
	{
		schedule_swap(current_root, current_node, previous_node);
		deep = 0;
	}
	else
		deep++;
	if (current_node->left != NULL)
	{
		schedule_separator(deep, &current_node->left, current_node);
		if (deep == 0)
			schedule_or_and(deep, &current_node->left, current_node);
	}
	if (current_node->right != NULL)
	{
		schedule_separator(deep, &current_node->right, current_node);
		if (deep == 0)
			schedule_or_and(deep, &current_node->right, current_node);
	}
	return (IS_SORT);
}

int	schedule_or_and(
	int deep,
	t_bnode **current_root,
	t_bnode *previous_node
)
{
	t_node_binary	*current_node;

	current_node = previous_node->left;
	if (*((char *)current_node->value) == SHELL_INSTRUCTION_COMMAND)
		return (IS_SORT);
	if (*((char *)current_node->value) == SHELL_SEPARATOR_TYPE_AND
		|| *((char *)current_node->value) == SHELL_SEPARATOR_TYPE_OR)
	{
		schedule_swap(current_root, current_node, previous_node);
		deep = 0;
	}
	else
		deep++;
	if (current_node->left != NULL)
	{
		schedule_or_and(deep, &current_node->left, current_node);
		// if (deep == 0)
			// schedule_pipe(deep, &current_node->left, current_node);
	}
	if (current_node->right != NULL)
	{
		schedule_or_and(deep, &current_node->right, current_node);
		// schedule_pipe(deep, &current_node->right, current_node);
	}
	return (IS_SORT);
}

// int	schedule_pipe(
// 	int deep,
// 	t_bnode **current_root,
// 	t_bnode *previous_node
// )
// {
// 	t_node_binary	*current_node;

// 	current_node = previous_node->left;
// 	if (*((char *)current_node->value) == SHELL_INSTRUCTION_COMMAND)
// 		return (IS_SORT);
// 	if (*((char *)current_node->value) == SHELL_SEPARATOR_TYPE_PIPE)
// 	{
// 		schedule_swap(current_root, current_node, previous_node);
// 		deep = 0;
// 	}
// 	else
// 		deep++;
// 	if (current_node->left != NULL)
// 		schedule_pipe(deep, &current_node->left, current_node);
// 	if (current_node->right != NULL)
// 		schedule_pipe(deep, &current_node->right, current_node);
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
// 		schedule_swap(current_root, current_node, previous_node);
// 	if (current_node->left != NULL)
// 	{
// 		schedule_or_and(&current_node->left, current_node);
// 		schedule_pipe(&current_node->left, current_node);
// 	}
// 	if (current_node->right != NULL)
// 	{
// 		schedule_or_and(&current_node->right, current_node);
// 		schedule_pipe(&current_node->right, current_node);
// 	}
// 	return (IS_SORT);
// }

// int	schedule_pipe(
// 	int deep,
// 	t_bnode **current_root,
// 	t_bnode *previous_node
// )
// {
// 	t_node_binary	*current_node;

// 	current_node = previous_node->left;
// 	if (*((char *)current_node->value) == SHELL_INSTRUCTION_COMMAND)
// 		return (IS_SORT);
// 	if (*((char *)current_node->value) == SHELL_SEPARATOR_TYPE_PIPE)
// 		schedule_swap(current_root, current_node, previous_node);
// 	if (current_node->left != NULL)
// 		schedule_pipe( &current_node->left, current_node);
// 	if (current_node->right != NULL)
// 		schedule_pipe( &current_node->right, current_node);
// 	return (IS_SORT);
// }

// int	schedule_command(t_shell_context *context, t_bnode *previous_node, t_bnode *current_root)
// {
// 	return (IS_SORT);
// }

// void	show_tree(t_bnode *root, int deep, char *pos)
// {
// 	ft_printf("Level:%d - side = %s\n", deep,  pos);
// 	if (*((char *)root->value) == SHELL_INSTRUCTION_COMMAND)
// 		ft_printf("Command = %s\n", ((t_shell_command *)root->value)->command_string);
// 	else
// 	{
// 		switch (*(char *)root->value)
// 		{
// 		case  SHELL_SEPARATOR_TYPE_AND:
// 			ft_printf("&&\n");
// 			break;
// 		case SHELL_SEPARATOR_TYPE_END:
// 			ft_printf(";\n");
// 			break;
// 		case SHELL_SEPARATOR_TYPE_PIPE:
// 			ft_printf("|\n");
// 			break;
// 		case SHELL_SEPARATOR_TYPE_OR:
// 			ft_printf("||\n");
// 			break;
// 		}
// 	}
// 	deep++;
// 	if (root->left)
// 		show_tree(root->left, deep, "left");
// 	if (root->right)
// 		show_tree(root->right, deep, "right");
// }

void	show_command(t_bnode *root, int deep)
{
	if (root->left)
		show_command(root->left, deep + 1);
	if (*((char *)root->value) == SHELL_INSTRUCTION_COMMAND)
		printf("%s", ((t_shell_command *)root->value)->command_string);
	else
	{
		switch (*(char *)root->value)
		{
		case  SHELL_SEPARATOR_TYPE_AND:
			printf("&&");
			break;
		case SHELL_SEPARATOR_TYPE_END:
			printf(";");
			break;
		case SHELL_SEPARATOR_TYPE_PIPE:
			printf("|");
			break;
		case SHELL_SEPARATOR_TYPE_OR:
			printf("||");
			break;
		}
	}
	if (root->right)
		show_command(root->right, deep + 1);
}