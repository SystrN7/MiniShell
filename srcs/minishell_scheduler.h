/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_scheduler.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:13:49 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/03 16:00:27 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SCHEDULER_H
# define MINISHELL_SCHEDULER_H

# include "libft.h"
# include "minishell_type.h"
# include "minishell_error.h"

/**
 * =============================================================================
 *									  Scheduler										
 * =============================================================================
 **/

t_bnode	*scheduler(
	t_shell_context *context,
	t_node_binary *unschedule_root
);

int		schedule(
	t_list	*priority,
	t_bnode **current_root,
	t_bnode *previous_node
);

t_list	*scheduler_get_priority_list(void);
t_bool	is_in_priority(char *priority, t_node_binary *node);

void	schedule_swap(
	t_bnode **current_root,
	t_bnode *current_node,
	t_bnode *previous_node
);

/**
 * =============================================================================
 *						 		 Consitency Analyser										
 * =============================================================================
 **/

t_bool	consistency_analyzer(t_shell_context *context, t_node_binary *root);
t_bool	separator_irregularity_identifier(
	t_shell_context *context,
	t_bnode *current_node
);

/**
 * =============================================================================
 *									  Utilities										
 * =============================================================================
 **/

char	get_node_type(t_node_binary *node);
t_bool	is_null_command(t_shell_command *command);

/**
 * =============================================================================
 *									  Debug										
 * =============================================================================
 **/

void	show_tree(t_bnode *root, int deep, char *pos);
void	show_command(t_bnode *root, int deep);
void	binnary_show(t_bnode *root, int space, char *side);

#endif
