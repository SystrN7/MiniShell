/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delet.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:11:39 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/22 17:11:41 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_termcaps.h"
#include "minishell_utilities.h"
#include "minishell_signal.h"

static void	term_get_size(int *cols, int *rows)
{
	struct winsize	ws;

	if (ioctl(0, TIOCGWINSZ, &ws) == 0)
	{
		*cols = ws.ws_col;
		*rows = ws.ws_row;
	}
	else
	{
		*cols = -1;
		*rows = -1;
	}
}

int	ft_delete_character(t_termcaps *s, t_shell_context *context)
{
	int	cols;
	int	rows;

	if (context->line_i > 0)
	{
		term_get_size(&cols, &rows);
		if (((s->prompt_len + context->line_i) % cols) == 0)
		{
			tputs(tigetstr("bw"), 1, ft_putchar);
			tputs(cursor_left, 1, ft_putchar);
			ft_putchar(' ');
		}
		else
		{
			tputs(tigetstr("le"), 1, ft_putchar);
			tputs(cursor_left, 1, ft_putchar);
			ft_putchar(' ');
			tputs(cursor_left, 1, ft_putchar);
		}
		context->line_buff[context->line_i] = '\0';
		return (context->line_i - 1);
	}
	else
		tputs(tigetstr("bl"), 1, ft_putchar);
	return (0);
}
