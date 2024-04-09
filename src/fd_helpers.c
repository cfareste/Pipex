/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:02:55 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/03/08 17:38:46 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_input_file(char *file_path)
{
	int	input_fd;

	if (access(file_path, F_OK) == -1)
		exit(handle_error(file_path));
	input_fd = open(file_path, O_RDONLY);
	if (input_fd == -1)
		exit(handle_error(NULL));
	return (input_fd);
}

int	open_output_file(char *file_path)
{
	int	output_fd;

	if (access(file_path, F_OK) == 0
		&& access(file_path, W_OK) == -1)
		exit(handle_error(file_path));
	output_fd = open(file_path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (output_fd == -1)
		exit(handle_error(NULL));
	return (output_fd);
}

int	close_fd(int *fd)
{
	if (*fd != -1 && close(*fd) == -1)
		return (-1);
	*fd = -1;
	return (1);
}
