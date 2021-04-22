#include "minishell_termcaps.h"
#include "minishell_utilities.h"
#include "minishell_signal.h"

int	ft_cpy_history(t_bidirectional_list **history, char line[2000])
{
	char	*buff;
	int		i;
	int		len;

	i = 0;
	buff = (char *)(*history)->content;
	len = ft_strlen(buff);
	while (i < len)
	{
		line[i] = buff[i];
		i++;
	}
	line[i] = '\0';
	return (i);
}

int	ft_set_histo_line(char line[2000],
	t_bidirectional_list **history, int id, t_termcaps *s)
{
	int	i;

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
		i = ft_cpy_history(history, line);
		s->first_histo = 1;
		return (i);
	}
	return (0);
}

int	ft_manage_history(t_termcaps *s, int id, t_shell_context *context,
		t_bidirectional_list **history)
{
	int	ret;

	tputs(tigetstr("cr"), 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
	tputs(tigetstr("DC"), 1, ft_putchar);
	s->prompt_len = console_prompt(context);
	ret = ft_set_histo_line(context->line_buff, history, id, s);
	write (1, context->line_buff, ret);
	return (ret);
}
