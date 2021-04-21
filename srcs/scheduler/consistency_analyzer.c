/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consistency_analyzer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:53:00 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/21 13:05:18 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_scheduler.h"

t_bool	consistency_analyzer(t_shell_context *context, t_node_binary *root)
{
	if (analyzer_recusive(context, root, root))
		return (TRUE);
	return (FALSE);
}

t_bool	analyzer_recusive(t_shell_context *context, t_node_binary *node)
{
	char	node_type;
	t_list	*it;

	if (node == NULL)
		return (FALSE);
	if (analyzer_recusive(context, node->left))
		return (TRUE);
	node_type = get_node_type(node);
	token_irregularity_identifier(context, node_type);
	if (node_type == SHELL_INSTRUCTION_COMMAND)
	{
		it = ((t_shell_command *)node->value)->redirection;
		while (it)
		{
			token_irregularity_identifier(
				context,
				((t_redirection_list *)it)->redirection_type);
			if (((t_redirection_list *)it)->redirection_file)
				token_irregularity_identifier(context,
					SHELL_REDIRECT_TYPE_FILE_NAME);
			it = it->next;
		}
	}
	if (analyzer_recusive(context, node->right))
		return (TRUE);
	return (FALSE);
}

t_bool	token_irregularity_identifier(t_shell_context *context, char token_id)
{
	static char	previous_token_id = SHELL_INSTRUCTION_UNKNOWN;
	char		token_separator[] = {
		SHELL_REDIRECT_TYPE_DOUBLE_LEFT,
		SHELL_REDIRECT_TYPE_DOUBLE_RIGHT,
		SHELL_REDIRECT_TYPE_LEFT,
		SHELL_REDIRECT_TYPE_RIGHT,
		SHELL_SEPARATOR_TYPE_END,
		SHELL_SEPARATOR_TYPE_PIPE,
		SHELL_SEPARATOR_TYPE_AND,
		SHELL_SEPARATOR_TYPE_OR,
		0
	};

	if (ft_is_in_charset(previous_token_id, token_separator)
		&& ft_is_in_charset(token_id, token_separator))
	{
		error_message(
			context,
			ERROR_SYNTAX_TOKEN_BOND, 258,
			token_separator_get_string(context, token_id));
		if (!context->interactive_mode)
			ft_printf_fd(standard_error, "%s : line %d: `%s'",
				context->shell_name, context->line_number, context->line);
		return (TRUE);
	}
	return (FALSE);
}

char	*token_separator_get_string(
	t_shell_context *context,
	char token_id
)
{
	char				*string;

	if (token_id == SHELL_SEPARATOR_TYPE_AND)
		string = "&&";
	else if (token_id == SHELL_SEPARATOR_TYPE_OR)
		string = "||";
	else if (token_id == SHELL_SEPARATOR_TYPE_END)
		string = ";";
	else if (token_id == SHELL_SEPARATOR_TYPE_PIPE)
		string = "|";
	else if (token_id == SHELL_REDIRECT_TYPE_RIGHT)
		string = ">";
	else if (token_id == SHELL_REDIRECT_TYPE_DOUBLE_RIGHT)
		string = ">>";
	else if (token_id == SHELL_REDIRECT_TYPE_LEFT)
		string = "<";
	else if (token_id == SHELL_REDIRECT_TYPE_DOUBLE_LEFT)
		string = "<<";
	else
		string = "?";
	return (string);
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

	error_message(
		context,
		ERROR_SYNTAX_TOKEN_BOND, 258,
		separator_string);
	if (!context->interactive_mode)
		ft_printf_fd(standard_error, "%s : line %d: `%s'",
			context->shell_name, context->line_number, context->line);
	return (TRUE);
}
