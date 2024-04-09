/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_helpers_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:41:58 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/03/08 18:00:40 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	**get_paths(char **envp)
{
	int		i;
	char	*aux;
	char	**paths;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], PATH_PREFIX, ft_strlen(envp[i])))
		i++;
	if (envp[i])
		paths = ft_split(envp[i] + ft_strlen(PATH_PREFIX), ':');
	else
		paths = ft_split(DEFAULT_PATH, ':');
	i = 0;
	while (paths && paths[i])
	{
		aux = paths[i];
		paths[i] = ft_strjoin(aux, "/");
		free(aux);
		if (!paths[i])
			return (NULL);
		i++;
	}
	return (paths);
}

int	close_pipes_fds(t_state *state)
{
	if (close_fd(&state->pipe_fds[0]) == -1
		|| close_fd(&state->pipe_fds[1]) == -1
		|| close_fd(&state->here_doc_fd) == -1)
		return (-1);
	return (0);
}

void	free_state(t_state *state)
{
	int	i;

	i = 0;
	while (state->paths && state->paths[i])
		free(state->paths[i++]);
	if (state->paths)
		free(state->paths);
	state->paths = NULL;
	if (state->limiter)
		free(state->limiter);
	state->limiter = NULL;
	if (close_pipes_fds(state) == -1)
		exit(handle_error(NULL));
}

int	init_state(t_state *state, int argc, char **argv, char **envp)
{
	state->argc = argc;
	state->argv = argv;
	state->envp = envp;
	state->pipe_fds[0] = -1;
	state->pipe_fds[1] = -1;
	state->here_doc_fd = -1;
	state->limiter = NULL;
	state->paths = get_paths(envp);
	if (!state->paths)
		return (0);
	state->here_doc = has_here_doc(state->argv[HERE_DOC_INDEX]);
	if (state->here_doc)
	{
		state->limiter = ft_strjoin(argv[HERE_DOC_INDEX + 1], "\n");
		if (state->here_doc && !state->limiter)
			return (0);
		state->here_doc_fd = read_from_here_doc(state);
	}
	return (1);
}
