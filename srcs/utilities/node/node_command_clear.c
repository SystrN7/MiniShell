/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_command_clear.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 11:43:18 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/22 12:05:21 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utilities.h"
#include "minishell_error.h"

int	node_command_clear(t_shell_command *command)
{
	int		i;

	if (command->command_string != NULL)
		ft_managed_free(command->command_string);
	if (command->command_mask != NULL)
		ft_managed_free(command->command_mask);
	if (command->path != NULL)
		ft_managed_free(command->path);
	if (command->argv != NULL)
	{
		i = 0;
		while (command->argv[i])
			ft_managed_free(command->argv[i++]);
		ft_managed_free(command->argv);
	}
	if (command->masks != NULL)
	{
		i = 0;
		while (command->masks[i])
			ft_managed_free(command->masks[i++]);
		ft_managed_free(command->masks);
	}
	if (command->redirection != NULL)
		node_command_redirections_clear(command->redirection);
	return (SUCCESS);
}

int	node_command_redirections_clear(t_redirection_list *redirections)
{
	t_redirection_list	*it;
	t_redirection_list	*previous;

	it = redirections;
	while (it)
	{
		if (it->redirection_file != NULL)
			ft_managed_free(it->redirection_file);
		if (it->mask != NULL)
			ft_managed_free(it->mask);
		previous = it;
		it = it->next;
		ft_managed_free(previous);
	}
	return (SUCCESS);
}
