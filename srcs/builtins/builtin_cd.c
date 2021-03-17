/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 10:23:55 by fgalaup           #+#    #+#             */
/*   Updated: 2021/03/17 11:19:11 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
** |================================ CD SPECS =================================|
** Withous params redirecting to the user home directory. (Use value of HOME).
** If params is ~ redirecting to the user home directory. (Use fixed value).
** If params is - change to the previous directory (Use value of OLDPWD).
** If empty args is given in frist args is just dont change of directory.
** If invalid path is specified (bash: cd: test/: No such file or directory).
** If valid path is specified change (Update OLDPWD and PWD)
*/

#include "minishell_builtin.h"
#include <sys/syslimits.h>

int	builtin_cd(t_shell_context *context, int argc, char **args)
{
	char	*directory;

	if (argc == 1)
		builtin_cd_no_arg(context, args[path]);
	else
	{
		directory = args[arg1];
		if (ft_strncmp(args[arg1], "-", 2))
			directory = env_get(context, "OLDPWD");
		if (chdir(args[arg1]) == ERROR_STD)
			error_message(context, ERROR_STD, 1);
		else
			builtin_cd_update_env(context);
	}
	return (context->last_command_return_code);
}

int	builtin_cd_no_arg(t_shell_context *context, char *builtin_name)
{
	char	*env_home;

	env_home = env_get(context, "HOME");
	if (env_home)
	{
		env_home = ft_lst_associative_get(context->shared_environment, "HOME");
		if (chdir(env_home) == ERROR_STD)
			error_message(context, ERROR_STD, 1);
		else
			builtin_cd_update_env(context);
	}
	else
		error_message(context, ERROR_BUILTIN_CD_NO_HOME, 1, builtin_name);
	return (SUCCESS);
}

int	builtin_cd_update_env(t_shell_context *context)
{
	char	*current_directory;
	char	*previous_directory;

	current_directory = ft_calloc(sizeof(char), PATH_MAX);
	getcwd(current_directory, PATH_MAX);
	previous_directory = env_get(context, "PWD");
	env_set(context, "OLDPWD", ft_strdup(previous_directory));
	env_set(context, "PWD", current_directory);
	return (SUCCESS);
}
