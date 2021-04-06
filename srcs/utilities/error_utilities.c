/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 16:20:20 by fgalaup           #+#    #+#             */
/*   Updated: 2021/04/05 16:28:36 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_error.h"

int	error_print_messages(
	t_shell_context *context,
	int error_code,
	int return_code,
	va_list args
)
{
	char	*buffer;
	int		size;
	char	*error_message;

	buffer = NULL;
	error_message = error_get_message(error_code);
	size = ft_format(error_message, args, &buffer);
	if (size < 0)
		exit(1);
	write(standard_error, buffer, size);
	write(standard_error, "\n", 1);
	ft_managed_free(buffer);
	context->last_command_return_code = return_code;
	return (return_code);
}

void	error_print_origin(va_list args)
{
	char	*error_message;

	error_message = (char *)va_arg(args, char *);
	while (error_message)
	{
		ft_printf_fd(standard_error, "%s: ", error_message);
		error_message = (char *)va_arg(args, char *);
	}
}

char	*error_get_message(int	error_code)
{
	size_t	i;

	if (error_code == ERROR_STD)
		return (strerror(errno));
	i = 0;
	while (error_messages[i].code != 0 && error_messages[i].message != NULL)
	{
		if (error_messages[i].code == error_code)
			return (error_messages[i].message);
		i++;
	}
	return (NULL);
}
