/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:01:34 by fgalaup           #+#    #+#             */
/*   Updated: 2021/02/17 13:06:55 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_utilities.h"

static void	print_binary(t_boolean value)
{
	if (value == TRUE)
		ft_printf("(True)\n");
	else if (value == FALSE)
		ft_printf("(False)\n");
	else
		ft_printf("%i\n", (int)value);
}

/**
 * Expected :
 * 	(True)
 * 	(True)
 * 	(False)
 * 	(True)
 * 	(True)
 * 	(True)
 * 	(False)
 * 	(False)
 * 
 **/


void	test_path_binary_existe(void)
{
	print_binary(path_find_binary("/bin", "ls"));
	print_binary(path_find_binary("/usr/bin", "top"));
	print_binary(path_find_binary("/usr/bin", "ls"));
	print_binary(path_find_binary("/Users/fgalaup/.brew/bin/", "bash"));
	print_binary(path_find_binary("/bin", "bash"));
	print_binary(path_find_binary("..", "minishell"));
	print_binary(path_find_binary("..", "minitest"));
	print_binary(path_find_binary("../.././././/../..", "minitest"));
}

/**
 * Expected :
 * 	/bin/ls
 * 	(null)
 * 	(null)
 * 	/bin/kill
 * 	/bin//ls
 * 	(null)
 * 	(null)
 * 	/bin//kill
 * 
 */

void	test_sample_path_resolution(void)
{
	char env_path_basic[] = "/bin";
	char env_path_basic_training_slash[] = "/bin/";
	char env_path_avenced[] = "/bin:/usr/bin";
	char env_path_complex[] = "/Users/fgalaup/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/opt/X11/bin:/Users/fgalaup/.brew/bin";
	// char env_path_relative[] = ".";

	ft_printf("%s\n", path_get_binary_path(env_path_basic, "ls"));
	ft_printf("%s\n", path_get_binary_path(env_path_basic, "make"));
	ft_printf("%s\n", path_get_binary_path(env_path_basic, "top"));
	ft_printf("%s\n", path_get_binary_path(env_path_basic, "kill"));

	ft_printf("%s\n", path_get_binary_path(env_path_basic_training_slash, "ls"));
	ft_printf("%s\n", path_get_binary_path(env_path_basic_training_slash, "top"));
	ft_printf("%s\n", path_get_binary_path(env_path_basic_training_slash, "kill"));

	ft_printf("%s\n", path_get_binary_path(env_path_avenced, "ls"));
	ft_printf("%s\n", path_get_binary_path(env_path_avenced, "top"));
	ft_printf("%s\n", path_get_binary_path(env_path_avenced, "kill"));
	ft_printf("%s\n", path_get_binary_path(env_path_avenced, "ls"));
	ft_printf("%s\n", path_get_binary_path(env_path_avenced, "make"));
	ft_printf("%s\n", path_get_binary_path(env_path_avenced, "top"));
	ft_printf("%s\n", path_get_binary_path(env_path_avenced, "bash"));
	ft_printf("%s\n", path_get_binary_path(env_path_avenced, "kill"));
	ft_printf("%s\n", path_get_binary_path(env_path_avenced, "sousle6tonejiji"));

	ft_printf("%s\n", path_get_binary_path(env_path_complex, "test"));
	ft_printf("%s\n", path_get_binary_path(env_path_complex, "top"));
	ft_printf("%s\n", path_get_binary_path(env_path_complex, "minikube"));
	ft_printf("%s\n", path_get_binary_path(env_path_complex, "docker"));
	ft_printf("%s\n", path_get_binary_path(env_path_complex, "x11perf"));
}
