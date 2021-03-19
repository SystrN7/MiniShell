/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:19:53 by seruiz            #+#    #+#             */
/*   Updated: 2021/03/19 15:17:27 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSER_H
# define MINISHELL_PARSER_H

# include "libft.h"

# include "minishell_type.h"
# include "minishell_error.h"

void	ft_treat_var(t_shell_context *context, t_shell_command *command);
void	ft_catch_redirection(t_shell_context *context, t_shell_command *cmd);
int		ft_redirection_right(t_shell_command *cmd, int i);
int		ft_redirection_left(t_shell_command *cmd, int i);
void	ft_lstadd_back_redirection(t_redirection_list **alst, t_redirection_list *new);

t_node_binary	*ft_treat_line(char *line);

typedef struct	s_parsing_struct
{
	t_node_binary	**root;
	t_node_binary	*node;
	t_shell_command	**str_root;
	t_shell_command	*str_struct;
}					t_parse_struct;

#endif
