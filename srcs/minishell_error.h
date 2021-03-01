/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:40:28 by fgalaup           #+#    #+#             */
/*   Updated: 2021/02/10 10:56:11 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ERROR_H
# define MINISHELL_ERROR_H

# include <errno.h>
# include <stdio.h>

# include "libft.h"

enum					e_error_code
{
	ERROR_MALLOC = -1,
	SUCCESS,
	ERROR_UNDIFINED,
	ERROR_STD,

};

static const struct		s_error_messages
{
	int					code;
	char				*message;
} error_messages[] = {
	{ ERROR_UNDIFINED, "Undifined error (Just take a cooffe ☕)." },
	{ ERROR_STD, "Is not an error for my bro." },
	
	{ 0, NULL}
};

int						ft_error(int error_code);
int						ft_std_error(void);

#endif
