/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_redirection_left.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:11:18 by seruiz            #+#    #+#             */
/*   Updated: 2021/03/19 15:16:36 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"
#include "minishell_builtin.h"
#include "minishell_utilities.h"
#include "minishell_parser.h"

#include <unistd.h>

void	ft_fill_new_str_left(t_shell_command *cmd, char *new_str, char *new_mask, t_redirection_list *lst, int j, int i)
{
	int	k;
	int	l;

	(void)lst;
	k = 0;
	printf("fill j = %d\nfill i = %d\n", j, i);
	while (k < j)
	{
		new_str[k] = cmd->command_string[k];
		new_mask[k] = cmd->command_mask[k];
		k++;
	}
	l = i;
	if (lst->redirection_type == SHELL_SEPARATOR_TYPE_REDIRECT_DOUBLE_LEFT)
		l++;
	l++;
	while (cmd->command_string[l])
	{
		new_str[k] = cmd->command_string[l];
		new_mask[k] = cmd->command_mask[l];
		k++;
		l++;
	}
}

void	ft_remove_file_name_left(t_shell_command *cmd, int len, int j, int i, t_redirection_list *lst)
{
	char	*new_str;
	char	*new_mask;
	int		k;
	int		l;
	int		total_len;

	(void)len;
	(void)lst;
	k = 0;
	l = 0;
	total_len = ft_strlen(cmd->command_string);
	if (lst->redirection_type == SHELL_SEPARATOR_TYPE_REDIRECT_DOUBLE_LEFT)
		total_len--;
	//total_len--;
	printf ("\nfinal str len = %d\n", total_len - i + j);
	new_str = ft_managed_malloc(sizeof(char) * (total_len - i + j + 1));
	new_mask = ft_managed_malloc(sizeof(char) * (total_len - i + j + 1));
	new_str[total_len - i + j] = '\0';
	new_mask[total_len - i + j] = '\0';
	//printf("new_str len = %d\n", total_len - len);

	ft_fill_new_str_left(cmd, new_str, new_mask, lst, j, i);

	printf("New_str = %s\n", new_str);
	printf("New_mask= %s\n", new_mask);
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
		new->redirection_type = SHELL_SEPARATOR_TYPE_REDIRECT_DOUBLE_LEFT;
		k++;
	}
	else
		new->redirection_type = SHELL_SEPARATOR_TYPE_REDIRECT_LEFT;
	k++;
	i--;
	printf ("i = %d\n", i);
	while (cmd->command_string[i] == ' ' && cmd->command_mask[i] == '0')
		i--;
	j = i;
	while (j >= 0 && ((cmd->command_string[j] != '>'
		&& cmd->command_string[j] != '<' && cmd->command_string[j] != ' ')
		|| cmd->command_mask[j] != '0'))
		j--;
	printf("index start filename = %d\n", j);
	printf("filename len = %d\n", i - j);
	new->redirection_file = ft_managed_malloc(sizeof(char) * (i - j + 1));
	new->redirection_file[i - j] = '\0';
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
	int	j;
	int	k;
	int	len;
	t_redirection_list	*new;

	len = i;
	new = ft_managed_malloc(sizeof(t_redirection_list));
	new->next = 0;
	k = 0;
	j = ft_skip_spaces_left(cmd, new, i);
	while (j >= 0 && ((cmd->command_string[j] != '>'
		&& cmd->command_string[j] != '<' && cmd->command_string[j] != ' ')
		|| cmd->command_mask[j] != '0'))
	{
		new->redirection_file[k] = cmd->command_string[j];
		j--;
		k++;
	}
	ft_reverse_filename(new);
	printf("index start filename after = %d\n", j);
	len = j - len;
	printf("File name = %s\n", new->redirection_file);
	ft_remove_file_name_left(cmd, len, j, i, new);
	ft_lstadd_back_redirection(cmd->redirection, new);
	return (0);
}
