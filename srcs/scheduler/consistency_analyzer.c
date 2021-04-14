/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consistency_analyzer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:53:00 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/12 16:14:22 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_scheduler.h"

t_bool	consistency_analyzer(t_shell_context *context, t_node_binary *root)
{
	if (root->left && get_node_type(root->left) == SHELL_INSTRUCTION_COMMAND)
	{
		if (redirection_consistency_analizer(context, root->left, FALSE))
			return (TRUE);
		if (is_null_command(root->left->value))
			return (separator_irregularity_identifier(context, root));
	}
	if (analyzer_recusive(context, root, root->left))
		return (TRUE);
	if (root->right)
	{
		if (redirection_consistency_analizer(context, root->right, FALSE))
			return (TRUE);
		if (is_null_command(root->right->value)
			&& get_node_type(root) != SHELL_SEPARATOR_TYPE_END)
			return (separator_irregularity_identifier(context, root));
	}
	return (FALSE);
}

t_bool	analyzer_recusive(
	t_shell_context *context,
	t_node_binary *parent_node,
	t_node_binary *node
)
{
	if (node->left)
	{
		if (get_node_type(node->left) != SHELL_INSTRUCTION_COMMAND)
		{
			if (analyzer_recusive(context, node, node->left) == TRUE)
				return (TRUE);
		}
		else
		{
			if (redirection_consistency_analizer(context, node->left, TRUE))
				return (TRUE);
			if (is_null_command(node->left->value))
				return (separator_irregularity_identifier(context, node));
		}
	}
	if (node->right)
	{
		if (redirection_consistency_analizer(context, node->right, FALSE))
			return (TRUE);
		if (is_null_command(node->right->value))
			return (separator_irregularity_identifier(context, parent_node));
	}
	return (FALSE);
}

t_bool	redirection_consistency_analizer(
	t_shell_context *context,
	t_node_binary *node,
	t_bool last
)
{
	t_redirection_list	*it;

	it = *(((t_shell_command *)node->value)->redirection);
	while (it)
	{
		ft_printf("file name='%s' mask='%s'\n", it->redirection_file, it->mask);
		if (it->redirection_file == NULL || (it->redirection_file[0] == '\0'))
		{
			if (last && it->next == NULL)
			{
				error_message(context, ERROR_SYNTAX_TOKEN_BOND, 258, "newline");
				return (TRUE);
			}
			return (redirection_irregularity_identifier(context, it));
		}
		it = it->next;
	}
	return (FALSE);
}

t_bool	redirection_irregularity_identifier(
	t_shell_context *context,
	t_redirection_list *redirection
)
{
	char				*redirection_string;

	if (redirection->redirection_type == SHELL_REDIRECT_TYPE_RIGHT)
		redirection_string = ">";
	else if (redirection->redirection_type == SHELL_REDIRECT_TYPE_DOUBLE_RIGHT)
		redirection_string = ">>";
	else if (redirection->redirection_type == SHELL_REDIRECT_TYPE_LEFT)
		redirection_string = "<";
	else if (redirection->redirection_type == SHELL_REDIRECT_TYPE_DOUBLE_LEFT)
		redirection_string = "<<";
	else
		redirection_string = "?";
	error_message(
		context,
		ERROR_SYNTAX_TOKEN_BOND, 258,
		redirection_string);
	return (TRUE);
}

t_bool	separator_irregularity_identifier(
	t_shell_context *context,
	t_bnode *current_node
)
{
	char	separator_type;
	char	*separator_string;

	separator_string = NULL;
	separator_type = *((char *)current_node->value);
	if (separator_type == SHELL_SEPARATOR_TYPE_AND)
		separator_string = "&&";
	else if (separator_type == SHELL_SEPARATOR_TYPE_OR)
		separator_string = "||";
	else if (separator_type == SHELL_SEPARATOR_TYPE_END)
		separator_string = ";";
	else if (separator_type == SHELL_SEPARATOR_TYPE_PIPE)
		separator_string = "|";
	else
		separator_string = "?";
	error_message(
		context,
		ERROR_SYNTAX_TOKEN_BOND, 258,
		separator_string);
	return (TRUE);
}
