/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:53:04 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/08 16:30:07 by seruiz           ###   ########lyon.fr   */
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
	cmd->redirection = ft_managed_malloc(sizeof(t_redirection_list *));
	cmd->redirection[0] = NULL;
	while (cmd->command_string[i])
	{
		if (cmd->command_string[i] == '>' && cmd->command_mask[i] == '0')
			i = ft_redirection_right(cmd, i);
		else if (cmd->command_string[i] == '<' && cmd->command_mask[i] == '0')
			i = ft_redirection_left_new(cmd, i);
		else
			i++;
	}
	cmd->argv = ft_split(cmd->command_string, ' ');
}

void	ft_catch_redirection_before(t_shell_command *cmd)
{
	int	i;

	i = 0;
	cmd->redirection = ft_managed_malloc(sizeof(t_redirection_list *));
	cmd->redirection[0] = NULL;
	while (cmd->command_string[i])
	{
		if (cmd->command_string[i] == '>' && cmd->command_mask[i] == '0')
			i = ft_redirection_right(cmd, i);
		else if (cmd->command_string[i] == '<' && cmd->command_mask[i] == '0')
			i = ft_redirection_left_new(cmd, i);
		else
			i++;
	}
	ft_split_mask(cmd, ' ');
}
