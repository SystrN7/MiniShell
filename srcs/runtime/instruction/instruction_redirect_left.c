/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_redirect_left.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 16:59:49 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/06 11:58:12 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"

// <

int		instruction_redirect_left(t_shell_context *context, t_node_binary *node)
{
	int		fd;

	fd = open((char *)node->right, O_RDONLY);
	if (fd == -1)
		error_occut("file not exsite");
	fd = dup2(fd, standard_input);
	if (fd == -1)
		error_occut("cannot dup2");
	run_instruction(context, node->left);
	fd = dup2(standard_input, fd);
	return (context->last_command_return_code);
}
