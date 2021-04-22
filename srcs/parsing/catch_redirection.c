/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:53:04 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/22 17:10:00 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"
#include "minishell_builtin.h"
#include "minishell_utilities.h"
#include "minishell_parser.h"

#include <unistd.h>

t_redirection_list	*ft_lstlast_redirection(t_redirection_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_redirection(t_redirection_list **alst,
		t_redirection_list *new)
{
	t_redirection_list	*lst;

	if (alst == NULL || new == NULL)
		return ;
	if (*alst != NULL)
	{
		lst = ft_lstlast_redirection(*alst);
		lst->next = new;
	}
	else
		*alst = new;
}

void	ft_catch_redirection(t_shell_context *context, t_shell_command *cmd)
{
	int	i;

	(void)context;
	i = 0;
	cmd->redirection = NULL;
	while (cmd->command_string[i])
	{
		if (cmd->command_string[i] == '>' && cmd->command_mask[i] == '0')
			i = ft_redirection_right(cmd, i);
		else if (cmd->command_string[i] == '<' && cmd->command_mask[i] == '0')
			i = ft_redirection_left(cmd, i);
		else
			i++;
	}
	cmd->argv = ft_split(cmd->command_string, ' ');
}

void	ft_catch_redirection_before(t_shell_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->command_string[i])
	{
		if (cmd->command_string[i] == '>' && cmd->command_mask[i] == '0')
			i = ft_redirection_right(cmd, i);
		else if (cmd->command_string[i] == '<' && cmd->command_mask[i] == '0')
			i = ft_redirection_left(cmd, i);
		else
			i++;
	}
	ft_split_mask(cmd, ' ');
}
