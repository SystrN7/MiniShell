/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:53:04 by seruiz            #+#    #+#             */
/*   Updated: 2021/03/18 15:26:31 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"
#include "minishell_builtin.h"
#include "minishell_utilities.h"

#include <unistd.h>
/*
void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *lst;

	if (alst == NULL || new == NULL)
		return ;
	if (*alst != NULL)
	{
		lst = ft_lstlast(*alst);
		lst->next = new;
	}
	else
		*alst = new;
}
*/

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_redirection_left(t_shell_command *cmd, int i)
{
	int	j;

	(void)cmd;
	(void)i;
	j = 0;
	return (j);
}

int	ft_redirection_right(t_shell_command *cmd, int i)
{
	int	j;
	int	k;
	t_redirection_list	*new;

	new = malloc(sizeof(t_redirection_list));
	(void)cmd;
	(void)i;
	j = 0;
	k = 0;
	if (cmd->command_string[i + 1] == '>' && cmd->command_mask[i + 1] == '0')
	{
		printf(">>\n");
		new->redirection_type = SHELL_SEPARATOR_TYPE_REDIRECT_DOUBLE_RIGHT;
		i++;
	}
	else
	{
		printf(">\n");
		new->redirection_type = SHELL_SEPARATOR_TYPE_REDIRECT_RIGHT;
	}
	i++;
	while (cmd->command_string[i] == ' ')
		i++;
	j = i;
	while (cmd->command_string[j] && (cmd->command_string[j] != '>' || cmd->command_string[j] != '<' || (cmd->command_string[j] != ' ' && cmd->command_mask[j] == '0')))
		j++;
	new->redirection_file = malloc(sizeof(char) * (j - i + 1));
	new->redirection_file[j - i] = '\0';

	j = i;
	while (cmd->command_string[j] && (cmd->command_string[j] != '>' || cmd->command_string[j] != '<' || (cmd->command_string[j] != ' ' && cmd->command_mask[j] == '0')))
	{
		new->redirection_file[k] = cmd->command_string[j];
		j++;
		k++;
	}
	printf("File name = %s\n", new->redirection_file);
	//ft_lstadd_back(&cmd->redirection, new);
	return (j);
}

int	ft_argv_list(t_shell_command *cmd, int i)
{
	int j;

	j = 0;
	(void)cmd;
	(void)i;
	return (1);
}

void	ft_catch_redirection(t_shell_context *context, t_shell_command *cmd)
{
	int	i;

	//Split pendant la recherche de redirections?

	(void)context;
	i = 0;

	while (cmd->command_string[i])
	{
		if (cmd->command_string[i] == '>' && cmd->command_mask[i] == '0')// && cmd->command_string[i - 1] != '\\')
			i = ft_redirection_right(cmd, i);
		else if (cmd->command_string[i] == '<' && cmd->command_mask[i] == '0')// && cmd->command_string[i - 1] != '\\')
			i = ft_redirection_left(cmd, i);
		else
		{
			i++;
			//i = ft_argv_list(cmd, i);
		}
	}
}
