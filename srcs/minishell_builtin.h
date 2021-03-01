/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:02:51 by fgalaup           #+#    #+#             */
/*   Updated: 2021/02/28 16:57:12 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILTIN_H
# define MINISHELL_BUILTIN_H

# include "libft.h"

# include "minishell_type.h"
# include "minishell_utilities.h"

# define BUILTIN_ECHO	"echo"
# define BUILTIN_ENV	"env"
# define BUILTIN_EXPORT	"export"
# define BUILTIN_UNSET	"unset"

# define BUILTIN_PWD	"pwd"
# define BUILTIN_CD		"cd"

# define BUILTIN_EXIT	"exit"

int		builtin_echo(t_shell_context *context, int argc, char **args);
int		builtin_env(t_shell_context *context, int argc, char **args);
int		builtin_export(t_shell_context *context, int argc, char **args);
int		builtin_unset(t_shell_context *context, int argc, char **args);

int		builtin_pwd(t_shell_context *context, int argc, char **args);
int		builtin_cd(t_shell_context *context, int argc, char **args);

int		builtin_exit(t_shell_context *context, int argc, char **args);

#endif


