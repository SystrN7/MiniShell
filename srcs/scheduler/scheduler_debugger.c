/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_debugger.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:00:01 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/28 16:43:20 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_scheduler.h"

void	node_show(void *content, char *side)
{
	ft_printf("%s:", side);
	if (*((char *)content) == SHELL_INSTRUCTION_COMMAND)
		ft_printf("(%s)", ((t_shell_command *)content)->command_string);
	else
	{
		switch (*(char *)content)
		{
			case  SHELL_SEPARATOR_TYPE_AND:
				ft_printf("(&&)");
				break;
			case SHELL_SEPARATOR_TYPE_END:
				ft_printf("(;)");
				break;
			case SHELL_SEPARATOR_TYPE_PIPE:
				ft_printf("(|)");
				break;
			case SHELL_SEPARATOR_TYPE_OR:
				ft_printf("(||)");
				break;
		}
	}
}

void	binnary_show(t_bnode *root, int space, char *side)
{
	if (root == NULL)
		return ;
	space += 4;
	binnary_show(root->right, space, "Right");
	ft_printf("\n");
	for (int i = 4; i < space; i++)
		ft_printf(" ");
	node_show(root->value, side);
	binnary_show(root->left, space, "Left");
}

void	show_command(t_bnode *root, int deep)
{
	if (root->left)
		show_command(root->left, deep + 1);
	if (*((char *)root->value) == SHELL_INSTRUCTION_COMMAND)
		printf("%s", ((t_shell_command *)root->value)->command_string);
	else
	{
		switch (*(char *)root->value)
		{
		case  SHELL_SEPARATOR_TYPE_AND:
			printf("&&");
			break;
		case SHELL_SEPARATOR_TYPE_END:
			printf(";");
			break;
		case SHELL_SEPARATOR_TYPE_PIPE:
			printf("|");
			break;
		case SHELL_SEPARATOR_TYPE_OR:
			printf("||");
			break;
		}
	}
	if (root->right)
		show_command(root->right, deep + 1);
}
