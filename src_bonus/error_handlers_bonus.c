/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:43:57 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/03/07 19:15:03 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	handle_error(char *error)
{
	if (!error)
		perror(DEFAULT_ERROR);
	else
	{
		custom_error(ERROR_PREFIX);
		perror(error);
	}
	return (1);
}

int	command_not_found_error(char *cmd)
{
	char	*message;

	message = ft_strjoin(cmd, ": Command not found\n");
	if (!cmd)
		return (handle_error(NULL));
	custom_error(ERROR_PREFIX);
	custom_error(message);
	return (1);
}

int	custom_error(char *error)
{
	int		written_byte;

	while (*error)
	{
		written_byte = write(STDERR_FILENO, error, 1);
		if (written_byte == -1)
			return (handle_error(NULL));
		error++;
	}
	return (1);
}
