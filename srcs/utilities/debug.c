/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:20:35 by fgalaup           #+#    #+#             */
/*   Updated: 2021/01/24 14:14:30 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Function : debug_print_env
** Decription : Print in stdout every environement varible givent in params.
** Parameter :
** 	-	(env string[]) the environement varible (need to be null termited)
**
** Return (void)
*/

void	debug_print_env(char *env[])
{
	int it;

	it = 0;
	while (env[it])
		ft_printf("%s\n", env[it++]);
}
