/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consistency_analyzer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:53:00 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/05 15:13:37 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_scheduler.h"

// ??? Test this case after bug parsing fix
// - | echo ;; echo ||;
t_bool	consistency_analyzer(t_shell_context *context, t_node_binary *root)
{
	if (root->left && get_node_type(root->left) == SHELL_INSTRUCTION_COMMAND)
		if (is_null_command(root->left->value))
			return (separator_irregularity_identifier(context, root));
	if (analyzer_recusive(context, root, root->left))
		return (TRUE);
	if (root->right && is_null_command(root->right->value))
		if (get_node_type(root) != SHELL_SEPARATOR_TYPE_END)
			return (separator_irregularity_identifier(context, root));
	return (FALSE);
}

t_bool	analyzer_recusive(
	t_shell_context *context,
	t_node_binary *parent_node,
	t_node_binary *node
)
{
	if (node->left || get_node_type(node) != SHELL_INSTRUCTION_COMMAND)
		if (analyzer_recusive(context, node, node->left) == TRUE)
			return (TRUE);
	if (node->right && is_null_command(node->right->value))
		return (separator_irregularity_identifier(context, parent_node));
	return (FALSE);
}


t_bool	separator_irregularity_identifier(
	t_shell_context *c,
	t_bnode *current_node
)
{
	char	separator_type;
	char	*separator_string;

	separator_type = *((char *)current_node->value);
	separator_string = "Unknown";
	if (separator_type == SHELL_SEPARATOR_TYPE_AND)
		separator_string = "&&";
	else if (separator_type == SHELL_SEPARATOR_TYPE_OR)
		separator_string = "||";
	else if (separator_type == SHELL_SEPARATOR_TYPE_END)
		separator_string = ";";
	else if (separator_type == SHELL_SEPARATOR_TYPE_PIPE)
		separator_string = "|";
	else
		error_fatal(c, ERROR_SYNTAX_SEPARATOR_UNKNOWN, 1, separator_type);
	error_message(c, ERROR_SYNTAX_SEPARATOR_BOND, 258, separator_string);
	return (TRUE);
}
