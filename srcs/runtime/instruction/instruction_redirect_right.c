/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_redirect_right.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:54:33 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/05 16:26:09 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_runtime.h"

// >

int		instruction_redirect_right(t_shell_context *context, t_node_binary *node)
{
	int		fd;

	fd = open((char *)node->left, O_CREAT | O_WRONLY);
	if (fd == -1)
		error_occut("file not exsite");
	fd = dup2(fd, standard_output);
	if (fd == -1)
		error_occut("cannot dup2");
	run_instruction(context, node->right);
	fd = dup2(standard_output, fd);
	return (context->last_command_return_code);
}
