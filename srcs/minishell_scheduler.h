/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_scheduler.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:13:49 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/22 16:38:54 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SCHEDULER_H
# define MINISHELL_SCHEDULER_H

# include "libft.h"
# include "minishell_type.h"
# include "minishell_error.h"

t_node_binary	*scheduler(
	t_shell_context *context,
	t_node_binary *unschedule_root
);

void	schedule_swap(
	t_bnode **current_root,
	t_bnode *current_node,
	t_bnode *previous_node
);

int	schedule_separator(
	t_shell_context *context,
	t_bnode **current_root,
	t_bnode *previous_node
);

int	schedule_or_and(
	t_shell_context *context,
	t_bnode **current_root,
	t_bnode *previous_node
);

int	schedule_pipe(
	t_shell_context *context,
	t_bnode **current_root,
	t_bnode *previous_node
);

t_bool	consistency_analyzer(t_shell_context *context, t_node_binary *root);
t_bool	separator_irregularity_identifier(
	t_shell_context *context,
	t_bnode *current_node
);

void show_tree(t_bnode *root, int deep, char *pos);
void show_command(t_bnode *root, int deep);

#endif
