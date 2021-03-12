/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:19:53 by seruiz            #+#    #+#             */
/*   Updated: 2021/03/12 10:45:53 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSER_H
# define MINISHELL_PARSER_H

# include "libft.h"

# include "minishell_type.h"
# include "minishell_error.h"

t_node_binary	*ft_treat_line(char *line);

typedef struct	s_parsing_struct
{
	t_node_binary	**root;
	t_node_binary	*node;
	t_shell_command	**str_root;
	t_shell_command	*str_struct;
}					t_parse_struct;

#endif
