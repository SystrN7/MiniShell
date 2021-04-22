#include "minishell_termcaps.h"
#include "minishell_utilities.h"
#include "minishell_signal.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int	ft_set_histo_line(char line[2000], t_bidirectional_list **history, int id, t_termcaps *s)
{
	int	len;
	int	i;
	char	*buff;

	if (*history != NULL)
	{
		if (id == 1 && s->first_histo == 1)
		{
			if ((*history)->next != NULL)
				(*history) = (*history)->next;
		}
		else if (id == 0 && s->first_histo == 1)
		{
			if ((*history)->prev != NULL)
				(*history) = (*history)->prev;
		}
		i = 0;
		buff = (char *)(*history)->content;
		len = ft_strlen(buff);
		while (i < len)
		{
			line[i] = buff[i];
			i++;
		}
		line[i] = '\0';
		s->first_histo = 1;
		return (i);
	}
	return (0);
}

static void	term_get_size(int *cols, int *rows)
{
	struct winsize ws;

	if (ioctl(0, TIOCGWINSZ, &ws) == 0) {
		*cols = ws.ws_col;
		*rows = ws.ws_row;
	} else
		*cols = *rows = -1;
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
		context->line_i--;
		return (context->line_i);
	}
		else
			tputs(tigetstr("bl"), 1, ft_putchar);
	return (0);
}

int	ft_manage_history(t_termcaps *s, int id, t_shell_context *context, t_bidirectional_list **history)
{
	int	ret;

	tputs(tigetstr("cr"), 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
	tputs(tigetstr("DC"), 1, ft_putchar);
	s->prompt_len = console_prompt(context);
	/*
	if (id == 0)
		write (1, "next", 4);//Ecrire la ligne de l'histo
	else
		write (1, "prev", 4);
	*/
	ret = ft_set_histo_line(context->line_buff, history, id, s);
	write (1, context->line_buff, ret);
	return (ret);
}

void	ft_get_line(t_termcaps *s, t_shell_context *context, t_bidirectional_list **history)
{
	while (42)
	{
		s->l = read(0, s->str, 16);
		if (!strcmp(s->str, "\e[A"))
			context->line_i = ft_manage_history(s, 1, context, history);
		else if (!strcmp(s->str, "\e[B"))
			context->line_i = ft_manage_history(s, 0, context, history);
		else if (*(s->str) == 127)
		{
			context->line_i = ft_delete_character(s, context);
		}
		else if (*(s->str) >= 32 && *(s->str) <= 126)
		{
			write(1, s->str, 1);
			context->line_buff[context->line_i] = s->str[0];
			context->line_i++;
		}
		else if (*(s->str) == 4)
		{
			if (context->line_i == 0)
				signal_exit(1);
		}
		else if (*(s->str) == '\n')
		{
			write (1, "\n", 1);
			context->line_buff[context->line_i] = '\0';
			//s->prompt_len = console_prompt(context);
			break;
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
	result = malloc(sizeof(char) * len + 1);
	result[len] = '\0';
	while (i < len)
	{
		result[i] = context->line_buff[i];
		i++;
	}
	return (result);
}

char	*terms_input_mode(t_shell_context *context, t_bidirectional_list **history)
{
	t_termcaps		*s;
	char			*line;
	struct termios	save;

	s = malloc(sizeof(t_termcaps));
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
	free(s);
	tcsetattr(0, TCSANOW, &save);
	return (line);
}
