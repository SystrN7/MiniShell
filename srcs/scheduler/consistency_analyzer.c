/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consistency_analyzer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:53:00 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/23 13:36:09 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_scheduler.h"

t_bool	consistency_analyzer(t_shell_context *context, t_node_binary *root)
{
	if (analyzer_recusive(context, root))
		return (FT_TRUE);
	if (token_irregularity_identifier(context, SHELL_END_LINE))
		return (FT_TRUE);
	return (FT_FALSE);
}

t_bool	analyzer_recusive(t_shell_context *context, t_node_binary *node)
{
	char				node_type;
	t_redirection_list	*it;

	if (node == NULL)
		return (FT_FALSE);
	if (analyzer_recusive(context, node->left))
		return (FT_TRUE);
	node_type = get_node_type(node);
	if (token_irregularity_identifier(context, node_type))
		return (FT_TRUE);
	if (node_type == SHELL_INSTRUCTION_COMMAND)
	{
		it = ((t_shell_command *)node->value)->redirection;
		while (it)
		{
			if (token_irregularity_identifier(context, it->redirection_type))
				return (FT_TRUE);
			if (it->redirection_file[0] != '\0'
				&& token_irregularity_identifier(context, SHELL_REDIRECT_FILE))
				return (FT_TRUE);
			it = it->next;
		}
	}
	return (analyzer_recusive(context, node->right));
}

t_bool	token_irregularity_identifier(t_shell_context *context, char token_id)
{
	static char	previous_token_id = SHELL_INSTRUCTION_UNKNOWN;

	if (token_id == SHELL_END_LINE
		&& previous_token_id == SHELL_SEPARATOR_TYPE_END)
		return (FT_FALSE);
	if (ft_is_in_charset(previous_token_id, context->token_separator)
		&& ft_is_in_charset(token_id, context->token_separator))
	{
		error_message(
			context,
			ERROR_SYNTAX_TOKEN_BOND, 258,
			token_separator_get_string(token_id));
		if (!context->interactive_mode)
			ft_printf_fd(standard_error, "%s: line %d: `%s'\n",
				context->shell_name, context->line_number, context->line);
		return (FT_TRUE);
	}
	previous_token_id = token_id;
	return (FT_FALSE);
}

char	*token_separator_get_list(void)
{
	char		token_separator[11];

	token_separator[0] = SHELL_INSTRUCTION_UNKNOWN;
	token_separator[1] = SHELL_REDIRECT_TYPE_DOUBLE_LEFT;
	token_separator[2] = SHELL_REDIRECT_TYPE_DOUBLE_RIGHT;
	token_separator[3] = SHELL_REDIRECT_TYPE_LEFT;
	token_separator[4] = SHELL_REDIRECT_TYPE_RIGHT;
	token_separator[5] = SHELL_SEPARATOR_TYPE_END;
	token_separator[6] = SHELL_SEPARATOR_TYPE_PIPE;
	token_separator[7] = SHELL_SEPARATOR_TYPE_AND;
	token_separator[8] = SHELL_SEPARATOR_TYPE_OR;
	token_separator[9] = SHELL_END_LINE;
	token_separator[10] = 0;
	return (ft_strdup(token_separator));
}

char	*token_separator_get_string(
	char token_id
)
{
	if (token_id == SHELL_INSTRUCTION_COMMAND)
		return ("cmd");
	else if (token_id == SHELL_SEPARATOR_TYPE_AND)
		return ("&&");
	else if (token_id == SHELL_SEPARATOR_TYPE_OR)
		return ("||");
	else if (token_id == SHELL_SEPARATOR_TYPE_END)
		return (";");
	else if (token_id == SHELL_SEPARATOR_TYPE_PIPE)
		return ("|");
	else if (token_id == SHELL_REDIRECT_TYPE_RIGHT)
		return (">");
	else if (token_id == SHELL_REDIRECT_TYPE_DOUBLE_RIGHT)
		return (">>");
	else if (token_id == SHELL_REDIRECT_TYPE_LEFT)
		return ("<");
	else if (token_id == SHELL_REDIRECT_TYPE_DOUBLE_LEFT)
		return ("<<");
	else if (token_id == SHELL_END_LINE)
		return ("newline");
	else
		return ("?");
}
