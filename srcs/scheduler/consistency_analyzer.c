/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consistency_analyzer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:53:00 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/17 16:09:30 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_scheduler.h"

t_bool	consistency_analyzer(t_shell_context *context, t_node_binary *root)
{
	if (analyzer_recusive(context, root, root))
		return (TRUE);
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
			// Continue recusion 
			if (analyzer_recusive(context, node, node->left) == TRUE)
				return (TRUE);
		}
		else if (redirection_consistency_analizer(context, parent_node, node->left))
			return (TRUE);
	}
	else
		return (separator_irregularity_identifier(context, node));
	if (parent_node == node && node->right == NULL)
	{
		if (get_node_type(node) != SHELL_SEPARATOR_TYPE_END)
			return (error_message(context, ERROR_SYNTAX_TOKEN_BOND, 258, "newline"));
		return (FALSE);
	}
	if (node->right == NULL)
		return (separator_irregularity_identifier(context, parent_node));
	else if (redirection_consistency_analizer(context, parent_node, node->right))
		return (TRUE);
	return (FALSE);
}

t_bool	redirection_consistency_analizer(
	t_shell_context *context,
	t_node_binary *previous_node,
	t_node_binary *node
)
{
	t_redirection_list	*it;

	it = *(((t_shell_command *)node->value)->redirection);
	while (it)
	{
		if (it->redirection_file == NULL || (it->redirection_file[0] == '\0'))
		{
			if (it->next)
				return (redirection_irregularity_identifier(context, it->next));
			else if (node == previous_node)
				error_message(context, ERROR_SYNTAX_TOKEN_BOND, 258, "newline");
			else if (previous_node)
				return (separator_irregularity_identifier(context, previous_node));
			else
				ft_printf("pascontent\n");
			return (TRUE);
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
	if (!context->interactive_mode)
		ft_printf_fd(standard_error, "%s : line %d: `%s'",
			context->shell_name, context->line_number, context->line);
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
	separator_type = get_node_type(current_node);
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
	if (!context->interactive_mode)
		ft_printf_fd(standard_error, "%s : line %d: `%s'",
			context->shell_name, context->line_number, context->line);
	return (TRUE);
}
