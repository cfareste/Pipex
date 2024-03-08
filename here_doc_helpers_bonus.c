/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_helpers_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:04:59 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/03/08 19:30:20 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	has_here_doc(char *argument)
{
	if (!ft_strncmp(argument, HERE_DOC, ft_strlen(argument)))
		return (1);
	return (0);
}

int	read_from_here_doc(t_state *state)
{
	int		here_doc_fds[2];
	int		prefix_length;
	char	*line;

	prefix_length = ft_strlen(HERE_DOC_PREFIX);
	if (pipe(here_doc_fds) == -1)
		exit(handle_error(NULL));
	if (write(STDOUT_FILENO, HERE_DOC_PREFIX, prefix_length) == -1)
		exit(handle_error(NULL));
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(line, state->limiter, ft_strlen(line)))
	{
		if (write(here_doc_fds[1], line, ft_strlen(line)) == -1)
			exit(handle_error(NULL));
		free(line);
		if (write(STDOUT_FILENO, HERE_DOC_PREFIX, prefix_length) == -1)
			exit(handle_error(NULL));
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	if (close_fd(&here_doc_fds[1]) == -1)
		exit(handle_error(NULL));
	return (here_doc_fds[0]);
}
