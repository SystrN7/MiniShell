/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:11:44 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/23 12:18:52 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_termcaps.h"
#include "minishell_utilities.h"
#include "minishell_signal.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	ft_exec_ctrl_D(t_shell_context *context)
{
	if (context->line_i == 0)
		signal_exit(1);
}

void	ft_get_line(t_termcaps *s, t_shell_context *context,
		t_bidirectional_list **history)
{
	while (42)
	{
		s->l = read(0, s->str, 16);
		if (!ft_strncmp(s->str, "\e[A", 4))
			context->line_i = ft_manage_history(s, 1, context, history);
		else if (!ft_strncmp(s->str, "\e[B", 4))
			context->line_i = ft_manage_history(s, 0, context, history);
		else if (*(s->str) == 127)
			context->line_i = ft_delete_character(s, context);
		else if (*(s->str) >= 32 && *(s->str) <= 126)
		{
			write(1, s->str, 1);
			context->line_buff[context->line_i] = s->str[0];
			context->line_i++;
		}
		else if (*(s->str) == 4)
			ft_exec_ctrl_D(context);
		else if (*(s->str) == '\n')
		{
			write (1, "\n", 1);
			context->line_buff[context->line_i] = '\0';
			break ;
		}
	}
}

char	*ft_copy_line(t_shell_context *context)
{
	int		len;
	int		i;
	char	*result;

	i = 0;
	len = context->line_i;
	if (len == 0)
		return (NULL);
	result = ft_managed_malloc(sizeof(char) * len + 1);
	result[len] = '\0';
	while (i < len)
	{
		result[i] = context->line_buff[i];
		i++;
	}
	return (result);
}

char	*terms_input_mode(t_shell_context *context,
		t_bidirectional_list **history)
{
	t_termcaps		*s;
	char			*line;
	struct termios	save;

	s = ft_managed_malloc(sizeof(t_termcaps));
	ft_memset(s, 0, sizeof(t_termcaps));
	s->first_histo = 0;
	s->term_name = getenv("TERM");
	tcgetattr(0, &(s->term));
	tcgetattr(0, &(save));
	(s->term).c_lflag &= ~(ECHO);
	(s->term).c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &(s->term));
	tgetent(0, s->term_name);
	context->line_buff[0] = '\0';
	context->line_i = 0;
	s->prompt_len = console_prompt(context);
	tputs(tigetstr("dm"), 1, ft_putchar);
	ft_get_line(s, context, history);
	line = ft_copy_line(context);
	ft_managed_free(s);
	tcsetattr(0, TCSANOW, &save);
	return (line);
}
