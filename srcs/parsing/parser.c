/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:18:34 by seruiz            #+#    #+#             */
/*   Updated: 2021/04/09 16:11:29 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parser.h"

int	ft_cat(char *dest, char *s, int j)
{
	int	i;

	i = 0;
	while (s[i])
	{
		dest[j] = s[i];
		i++;
		j++;
	}
	return (j);
}

int	ft_set_redirection(t_node_binary *root)
{
	t_node_binary	*it;

	it = root;

	if (*((char*)(root->value)) == SHELL_INSTRUCTION_COMMAND)
		ft_catch_redirection_before((t_shell_command *)(root->value));
	while (it)
	{
		if (it->left != NULL)
			break ;
		if (*((char*)(it->left->value)) == SHELL_INSTRUCTION_COMMAND)
			ft_catch_redirection_before((t_shell_command *)(it->left->value));
		if (*((char*)(it->right->value)) == SHELL_INSTRUCTION_COMMAND)
			ft_catch_redirection_before((t_shell_command *)(it->right->value));
		it = it->left;
	}
	return (0);
}

t_parse_struct	*ft_setup_parse_struct(void)
{
	t_parse_struct	*ret;

	ret = ft_managed_malloc(sizeof(t_parse_struct));
	ret->str_struct = ft_new_str_struct();
	ret->root = ft_managed_malloc(sizeof(t_node_binary *));
	ret->str_root = ft_managed_malloc(sizeof(t_shell_command *));
	ret->node = ft_binarytree_node_create(NULL);
	ret->str_root[0] = ret->str_struct;
	ret->root[0] = ret->node;
	ret->node->left = NULL;
	ret->node->right = NULL;
	return (ret);
}

t_node_binary	*ft_treat_line(char *line)
{
	int				j;
	t_parse_struct	*s;

	s = ft_setup_parse_struct();
	j = 0;
	while (line[j])
	{
		if (ft_is_separator(line, j) == 1)
			j = ft_separator(line, s->root, j, s->str_root);
		if (line[j] != '\'' && line[j] != '\"')
			j = ft_no_quote(line, j, s->str_root[0]);
		else if (line[j] == '\'')
			j = ft_single_quote(line, j, s->str_root[0]);
		else if (line[j] == '\"')
			j = ft_double_quote(line, j, s->str_root[0]);
	}
	if ((s->root[0])->value == NULL)
		(s->root[0])->value = (s->str_root[0]);
	else if ((s->root[0])->right == NULL)
		(s->root[0])->right = ft_binarytree_node_create((s->str_root[0]));
	ft_set_redirection(*(s->root));
	return (s->root[0]);
}
