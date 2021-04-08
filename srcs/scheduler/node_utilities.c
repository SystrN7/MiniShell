/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:59:02 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/08 11:16:03 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_scheduler.h"

t_bool	is_in_priority(char *priority, t_node_binary *node)
{
	char	node_type;
	size_t	i;

	i = 0;
	node_type = get_node_type(node);
	while (priority[i])
		if (priority[i++] == node_type)
			return (TRUE);
	return (FALSE);
}

t_bool 	is_null_command(t_shell_command *command)
{
	if (command->command_string == NULL || command->command_string[0] == '\0')
		return (TRUE);
	return (FALSE);
}
