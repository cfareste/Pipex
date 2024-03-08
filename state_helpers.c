/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:41:58 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/03/08 17:39:17 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		|| close_fd(&state->pipe_fds[1]) == -1)
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
	state->paths = get_paths(envp);
	if (!state->paths)
		return (0);
	return (1);
}
