/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 10:23:55 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/16 17:14:44 by fgalaup          ###   ########lyon.fr   */
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
	if (argc == 1)
		builtin_cd_no_arg(context, args[path]);
	else
	{
		if (!builtin_cd_previous(context, args[path], args[arg1]))
			return (context->last_command_return_code);
		if (chdir(args[arg1]) == ERROR_STD)
			error_builtin(context, ERROR_STD, 1, args[path], args[arg1], NULL);
		else
			builtin_cd_update_env(context);
	}
	return (context->last_command_return_code);
}

int	builtin_cd_no_arg(t_shell_context *context, char *builtin_name)
{
	return (builtin_cd_path_env(context, builtin_name, "HOME"));
}

int	builtin_cd_previous(t_shell_context *context, char *builtinname, char *arg1)
{
	int	status;

	if (!ft_strncmp(arg1, "-", 2))
	{
		status = builtin_cd_path_env(context, builtinname, "OLDPWD");
		if (status == SUCCESS)
			builtin_pwd(context, 0, NULL);
		else if (status == 2)
			ft_putchar_fd(standard_output, '\n');
		return (SUCCESS);
	}
	return (1);
}

int	builtin_cd_path_env(t_shell_context *context, char *blt_name, char *env_var)
{
	char	*env_home;

	env_home = env_get(context, env_var);
	if (env_home)
	{
		if (env_home[0] == '\0')
			return (2);
		if (chdir(env_home) == ERROR_STD)
			return (error_builtin(context, -1, 1, blt_name, env_home, NULL));
		else
			builtin_cd_update_env(context);
	}
	else
		return (error_builtin(
				context,
				ERROR_BUILTIN_CD_NO_VAR, 1,
				blt_name, NULL, env_var));
	return (SUCCESS);
}

int	builtin_cd_update_env(t_shell_context *context)
{
	char	*current_directory;
	char	*previous_directory;

	current_directory = ft_calloc(sizeof(char), PATH_MAX);
	getcwd(current_directory, PATH_MAX);
	previous_directory = env_get(context, "PWD");
	if (previous_directory != NULL)
		env_set(context, "OLDPWD", ft_strdup(previous_directory));
	if (current_directory != NULL)
		env_set(context, "PWD", current_directory);
	return (SUCCESS);
}
