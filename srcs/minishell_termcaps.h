#ifndef MINISHELL_TERMCAPS_H
# define MINISHELL_TERMCAPS_H

#include <curses.h>
#include <term.h>
#include <termios.h>
#include <sys/ioctl.h>

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#include <string.h>
#include "minishell_type.h"

typedef struct		s_termcaps
{
	char			str[16];
	char			line[2048];
	int				i;
	int				l;
	int				col;
	int				prompt_len;
	struct termios	term;
	char			*term_name;
}					t_termcaps;

char	*terms_input_mode(t_shell_context *context, t_bidirectional_list *history);

#endif