/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_redirection_left.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:11:18 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/22 12:18:08 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"
#include "minishell_builtin.h"
#include "minishell_utilities.h"
#include "minishell_parser.h"

#include <unistd.h>

void	ft_fill_new_str_left(t_shell_command *cmd, char *new_str,
		t_redirection_list *lst, int ij[2])
{
	int	k;
	int	l;

	(void)lst;
	k = 0;
	while (k < ij[1])
	{
		new_str[k] = cmd->command_string[k];
		k++;
	}
	l = ij[0];
	if (lst->redirection_type == SHELL_REDIRECT_TYPE_DOUBLE_LEFT)
		l++;
	l++;
	while (cmd->command_string[l])
	{
		new_str[k] = cmd->command_string[l];
		k++;
		l++;
	}
}

void	ft_fill_new_mask_left(t_shell_command *cmd,
		char *new_mask, t_redirection_list *lst, int ij[2])
{
	int	k;
	int	l;

	(void)lst;
	k = 0;
	while (k < ij[1])
	{
		new_mask[k] = cmd->command_mask[k];
		k++;
	}
	l = ij[0];
	if (lst->redirection_type == SHELL_REDIRECT_TYPE_DOUBLE_LEFT)
		l++;
	l++;
	while (cmd->command_string[l])
	{
		new_mask[k] = cmd->command_mask[l];
		k++;
		l++;
	}
}

void	ft_remove_file_name_left(t_shell_command *cmd, int j, int i,
		t_redirection_list *lst)
{
	char	*new_str;
	char	*new_mask;
	int		total_len;
	int		ij[2];

	(void)lst;
	total_len = ft_strlen(cmd->command_string);
	if (lst->redirection_type == SHELL_REDIRECT_TYPE_DOUBLE_LEFT)
		total_len--;
	if (j == 0)
		j = -1;
	new_str = ft_managed_malloc(sizeof(char) * (total_len - i + j + 1));
	new_mask = ft_managed_malloc(sizeof(char) * (total_len - i + j + 1));
	new_str[total_len - i + j] = '\0';
	new_mask[total_len - i + j] = '\0';
	ij[0] = i;
	ij[1] = j;
	ft_fill_new_str_left(cmd, new_str, lst, ij);
	ft_fill_new_mask_left(cmd, new_mask, lst, ij);
	ft_managed_free(cmd->command_string);
	cmd->command_string = new_str;
	ft_managed_free(cmd->command_mask);
	cmd->command_mask = new_mask;
}

int	ft_skip_spaces_left(t_shell_command *cmd,t_redirection_list *new, int i)
{
	int	j;
	int	k;

	k = i;
	if (cmd->command_string[i + 1] == '<' && cmd->command_mask[i + 1] == '0')
	{
		new->redirection_type = SHELL_REDIRECT_TYPE_DOUBLE_LEFT;
		k++;
	}
	else
		new->redirection_type = SHELL_REDIRECT_TYPE_LEFT;
	k++;
	i--;
	while (cmd->command_string[i] == ' ' && cmd->command_mask[i] == '0')
		i--;
	j = i;
	while (j >= 0 && ((cmd->command_string[j] != '>'
			&& cmd->command_string[j] != '<' && cmd->command_string[j] != ' ')
			|| cmd->command_mask[j] != '0'))
		j--;
	new->redirection_file = ft_managed_malloc(sizeof(char) * (i - j + 1));
	new->mask = ft_managed_malloc(sizeof(char) * (i - j + 1));
	new->redirection_file[i - j] = '\0';
	new->mask[i - j] = '\0';
	return (i);
}

void	ft_reverse_filename(t_redirection_list *new)
{
	int	i;
	int	j;
	char	*buff;

	i = 0;
	j = ft_strlen(new->redirection_file);
	buff = ft_managed_malloc(sizeof(char) * (j + 1));
	buff[j] = '\0';
	j--;
	while (new->redirection_file[i])
	{
		buff[j] = new->redirection_file[i];
		i++;
		j--;
	}
	ft_managed_free(new->redirection_file);
	new->redirection_file = buff;
}

int	ft_redirection_left(t_shell_command *cmd, int i)
{
	int					j;
	int					k;
	t_redirection_list	*new;

	new = ft_managed_malloc(sizeof(t_redirection_list));
	new->next = 0;
	k = 0;
	j = ft_skip_spaces_left(cmd, new, i);
	while (j >= 0 && ((cmd->command_string[j] != '>'
				&& cmd->command_string[j] != '<'
				&& cmd->command_string[j] != ' ')
			|| cmd->command_mask[j] != '0'))
	{
		new->redirection_file[k] = cmd->command_string[j];
		new->mask[k] = cmd->command_string[j];
		j--;
		k++;
	}
	ft_reverse_filename(new);
	ft_remove_file_name_left(cmd, j, i, new);
	ft_lstadd_back_redirection(&cmd->redirection, new);
	return (0);
}
