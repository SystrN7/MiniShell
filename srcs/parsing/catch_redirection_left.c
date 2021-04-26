/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_redirection_left.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 16:44:56 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/26 15:27:10 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"
#include "minishell_builtin.h"
#include "minishell_utilities.h"
#include "minishell_parser.h"

#include <unistd.h>

void	ft_fill_new_str_left(
	t_shell_command *c,
	char *new_str,
	char *new_mask,
	t_redirection_list *lst
)
{
	int	k;
	int	l;

	k = 0;
	while (c->command_string[k] != '<' || c->command_mask[k] != '0')
	{
		new_str[k] = c->command_string[k];
		new_mask[k] = c->command_mask[k];
		k++;
	}
	l = k;
	if (lst->redirection_type == SHELL_REDIRECT_TYPE_DOUBLE_LEFT)
		k++;
	k++;
	while (c->command_string[k] == ' ' && c->command_mask[k] == '0')
		k++;
	while (c->command_string[k] && ((c->command_string[k] != '>'
				&& c->command_string[k] != '<' && c->command_string[k] != ' ')
			|| c->command_mask[k] != '0'))
		k++;
	while (c->command_string[k])
	{
		new_mask[l] = c->command_mask[k];
		new_str[l++] = c->command_string[k++];
	}
}

void	ft_remove_file_name_left(
	t_shell_command *cmd, int len,
	t_redirection_list *lst
)
{
	char	*new_str;
	char	*new_mask;
	int		total_len;

	total_len = ft_strlen(cmd->command_string);
	new_str = ft_managed_malloc(sizeof(char) * (total_len - len + 1));
	new_mask = ft_managed_malloc(sizeof(char) * (total_len - len + 1));
	new_str[total_len - len] = '\0';
	new_mask[total_len - len] = '\0';
	ft_fill_new_str_left(cmd, new_str, new_mask, lst);
	ft_managed_free(cmd->command_string);
	cmd->command_string = new_str;
	ft_managed_free(cmd->command_mask);
	cmd->command_mask = new_mask;
}

int	ft_skip_spaces_left(t_shell_command *cmd, t_redirection_list *new, int i)
{
	int	j;

	j = 0;
	if (cmd->command_string[i + 1] == '<' && cmd->command_mask[i + 1] == '0')
	{
		new->redirection_type = SHELL_REDIRECT_TYPE_DOUBLE_LEFT;
		i++;
	}
	else
		new->redirection_type = SHELL_REDIRECT_TYPE_LEFT;
	i++;
	while (cmd->command_string[i] == ' ' && cmd->command_mask[i] == '0')
		i++;
	j = i;
	while (cmd->command_string[j] && ((cmd->command_string[j] != '>'
				&& cmd->command_string[j] != '<'
				&& cmd->command_string[j] != ' ')
			|| cmd->command_mask[j] != '0'))
		j++;
	new->redirection_file = ft_managed_malloc(sizeof(char) * (j - i + 1));
	new->redirection_file[j - i] = '\0';
	return (i);
}

int	ft_redirection_left(t_shell_command *cmd, int i)
{
	int					j;
	int					k;
	int					len;
	t_redirection_list	*new;

	len = i;
	new = ft_managed_malloc(sizeof(t_redirection_list));
	new->source_fd = -1;
	new->next = NULL;
	k = 0;
	j = ft_skip_spaces_left(cmd, new, i);
	while (cmd->command_string[j] && ((cmd->command_string[j] != '>'
				&& cmd->command_string[j] != '<'
				&& cmd->command_string[j] != ' ')
			|| cmd->command_mask[j] != '0'))
	{
		new->redirection_file[k] = cmd->command_string[j];
		j++;
		k++;
	}
	len = j - len;
	ft_remove_file_name_left(cmd, len, new);
	ft_lstadd_back_redirection(&cmd->redirection, new);
	return (0);
}
