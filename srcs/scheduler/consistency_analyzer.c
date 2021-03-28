/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consistency_analyzer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:53:00 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/28 16:40:52 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_scheduler.h"

void	binnary_show(t_bnode *root, int space, char *side);


// ??? Gros connard de merde pence a fix ls;&&|cat 
t_bool	consistency_analyzer(t_shell_context *context, t_node_binary *root)
{
	t_node_binary	*it;

	it = root;
	while (get_node_type(it) != SHELL_INSTRUCTION_COMMAND)
	{
		if (is_null_command(it->right->value))
		{	
			if (get_node_type(it->left) == SHELL_INSTRUCTION_COMMAND)
			{
				if (get_node_type(it) != SHELL_SEPARATOR_TYPE_END
					|| is_null_command(it->left->value))
					return (separator_irregularity_identifier(context, it));
			}
			else
				return (separator_irregularity_identifier(context, it->left));
		}
		else if (get_node_type(it->left) == SHELL_INSTRUCTION_COMMAND)
		{
			if (is_null_command(it->left->value))
				return (separator_irregularity_identifier(context, it));
		}
		it = it->left;
	}
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
		error_fatal(c, ERROR_SYNTAX_SEPARATOR_UNKNOWN, 258, separator_type);
	error_message(c, ERROR_SYNTAX_SEPARATOR_BOND, 258, separator_string);
	return (TRUE);
}
