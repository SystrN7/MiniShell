/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:19:53 by seruiz            #+#    #+#             */
/*   Updated: 2021/03/17 14:34:44 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSER_H
# define MINISHELL_PARSER_H

# include "libft.h"

# include "minishell_type.h"
# include "minishell_error.h"

void	ft_treat_var(t_shell_context *context, t_shell_command *command);

t_node_binary	*ft_treat_line(char *line);

typedef struct	s_parsing_struct
{
	t_node_binary	**root;
	t_node_binary	*node;
	t_shell_command	**str_root;
	t_shell_command	*str_struct;
}					t_parse_struct;

#endif
