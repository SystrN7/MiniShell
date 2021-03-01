/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 11:06:35 by fgalaup           #+#    #+#             */
/*   Updated: 2021/02/08 15:36:38 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
** |============================== EXPORT SPECS ===============================|
** Withous params is show all enviroment vars formated
** (declare -x VAR_NAME="VALUE")\n.
** If var is allready define with VAR_NAME=VALUE is move in enviromenent vars.
** Change of PWD OLDPWD dosent affect current shell location
** Exported var is affect if ther value as change
*/

#include "minishell_builtin.h"

int		builtin_export(t_shell_context *context, int argv, char **args)
{
	return (0);
}
