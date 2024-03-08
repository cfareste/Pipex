/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:56:02 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/03/08 17:48:28 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	init_child_processes(t_state *state)
{
	int	i;
	int	last_cmd_index;

	i = FIRST_COMMAND_INDEX;
	last_cmd_index = state->argc - 2;
	while (i <= last_cmd_index)
	{
		if (i < last_cmd_index && pipe(state->pipe_fds) == -1)
			exit(handle_error(NULL));
		state->pid = fork();
		if (state->pid == -1)
			exit(handle_error(NULL));
		else if (state->pid == 0)
			execute_command(state, i, last_cmd_index);
		if (i < last_cmd_index
			&& dup2(state->pipe_fds[0], STDIN_FILENO) == -1)
			exit(handle_error(NULL));
		if (close_pipes_fds(state) == -1)
			exit(handle_error(NULL));
		i++;
	}
	if (close(STDIN_FILENO) == -1)
		exit(handle_error(NULL));
	return (i - FIRST_COMMAND_INDEX);
}

static int	wait_for_child_processes(int cmds_count, t_state *state)
{
	int	status;

	while (cmds_count > 0)
	{
		if (state->pid == wait(&state->status) && WIFEXITED(state->status))
			status = WEXITSTATUS(state->status);
		cmds_count--;
	}
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	t_state	state;
	int		cmds_count;
	int		status;

	if (argc != 5)
		return (custom_error("Error: Invalid number of arguments\n"));
	if (!init_state(&state, argc, argv, envp))
		return (handle_error(NULL));
	cmds_count = init_child_processes(&state);
	status = wait_for_child_processes(cmds_count, &state);
	return (free_state(&state), status);
}
