/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:53:04 by seruiz            #+#    #+#             */
/*   Updated: 2021/03/19 11:57:13 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"
#include "minishell_builtin.h"
#include "minishell_utilities.h"

#include <unistd.h>

t_redirection_list	*ft_lstlast_redirection(t_redirection_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_redirection(t_redirection_list **alst, t_redirection_list *new)
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



int	ft_redirection_left(t_shell_command *cmd, int i)
{
	int	j;

	(void)cmd;
	(void)i;
	j = 0;
	return (j);
}

void	ft_remove_file_name(t_shell_command *cmd, int i, int len, t_redirection_list *lst)
{
	char	*new_str;
	char	*new_mask;
	int		k;
	int		l;
	int		total_len;

	(void)i;
	k = 0;
	l = 0;
	total_len = ft_strlen(cmd->command_string);
	new_str = ft_managed_malloc(sizeof(char) * (total_len - len + 1));
	new_mask = ft_managed_malloc(sizeof(char) * (total_len - len + 1));
	new_str[total_len - len] = '\0';
	new_mask[total_len - len] = '\0';
	printf("new_str len = %d\n", total_len - len);
	while (cmd->command_string[k] != '>' && cmd->command_mask[k] == '0')
	{
		new_str[k] = cmd->command_string[k];
		new_mask[k] = cmd->command_mask[k];
		k++;
	}
	l = k;
	if (lst->redirection_type == SHELL_SEPARATOR_TYPE_REDIRECT_DOUBLE_RIGHT)
		k += 2;
	else
		k++;
	while (cmd->command_string[k] == ' ')
		k++;
	while (cmd->command_string[k] && ((cmd->command_string[k] != '>' && cmd->command_string[k] != '<' && cmd->command_string[k] != ' ') || cmd->command_mask[k] != '0'))
		k++;
	while (cmd->command_string[k])
	{
		new_mask[l] = cmd->command_mask[k];
		new_str[l] = cmd->command_string[k];
		l++;
		k++;
	}
	printf("New_str = %s\n", new_str);
	printf("New_mask= %s\n", new_mask);
	ft_managed_free(cmd->command_string);
	cmd->command_string = new_str;
	ft_managed_free(cmd->command_mask);
	cmd->command_mask = new_mask;
}

int	ft_redirection_right(t_shell_command *cmd, int i)
{
	int	j;
	int	k;
	int	len;
	t_redirection_list	*new;

	len = i;
	new = ft_managed_malloc(sizeof(t_redirection_list));
	new->next = 0;
	(void)cmd;
	(void)i;
	j = 0;
	k = 0;
	if (cmd->command_string[i + 1] == '>' && cmd->command_mask[i + 1] == '0')
	{
		new->redirection_type = SHELL_SEPARATOR_TYPE_REDIRECT_DOUBLE_RIGHT;
		i++;
	}
	else
		new->redirection_type = SHELL_SEPARATOR_TYPE_REDIRECT_RIGHT;
	i++;
	while (cmd->command_string[i] == ' ' && cmd->command_mask[i] == '0')
		i++;
	j = i;
	while (cmd->command_string[j] && ((cmd->command_string[j] != '>' && cmd->command_string[j] != '<' && cmd->command_string[j] != ' ') || cmd->command_mask[j] != '0'))
		j++;
	new->redirection_file = ft_managed_malloc(sizeof(char) * (j - i + 1));
	new->redirection_file[j - i] = '\0';

	j = i;
	while (cmd->command_string[j] && ((cmd->command_string[j] != '>' && cmd->command_string[j] != '<' && cmd->command_string[j] != ' ') || cmd->command_mask[j] != '0'))
	{
		new->redirection_file[k] = cmd->command_string[j];
		j++;
		k++;
	}
	len = j - len;
	printf("File name = %s\n", new->redirection_file);
	ft_remove_file_name(cmd, i, len, new);
	ft_lstadd_back_redirection(cmd->redirection, new);
	return (0);
}

int	ft_argv_list(t_shell_command *cmd, int i)
{
	int j;

	j = 0;
	(void)cmd;
	(void)i;
	return (1);
}

void	ft_show_redirection_list(t_redirection_list **root)
{
	t_redirection_list	*lst;

	lst = *root;
	while (lst)
	{
		printf("redirection type = %d\n", lst->redirection_type);
		printf("redirection file = %s\n\n", lst->redirection_file);
		lst = lst->next;
	}
}

void	ft_catch_redirection(t_shell_context *context, t_shell_command *cmd)
{
	int	i;
	//Gerer les redirections et les retirer de la chaine principale. Ensuite spilt le chaine et metttre dans argv

	(void)context;
	i = 0;
	cmd->redirection = ft_managed_malloc(sizeof(t_redirection_list *));
	cmd->redirection[0] = NULL;
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
	ft_show_redirection_list(cmd->redirection);
}
