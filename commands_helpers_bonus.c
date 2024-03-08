/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_helpers_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:44:26 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/03/08 18:44:12 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	redirect_first_command(t_state *state)
{
	int	input_fd;

	if (state->here_doc)
		input_fd = state->here_doc_fd;
	else
		input_fd = open_input_file(state->argv[1]);
	if (dup2(input_fd, STDIN_FILENO) == -1
		|| dup2(state->pipe_fds[1], STDOUT_FILENO) == -1)
		exit(handle_error(NULL));
	if ((!state->here_doc && close_fd(&input_fd) == -1)
		|| close_pipes_fds(state) == -1)
		exit(handle_error(NULL));
}

static void	redirect_middle_command(t_state *state)
{
	if (dup2(state->pipe_fds[1], STDOUT_FILENO) == -1)
		exit(handle_error(NULL));
	if (close_pipes_fds(state) == -1)
		exit(handle_error(NULL));
}

static void	redirect_last_command(t_state *state)
{
	int	output_fd;

	output_fd = open_output_file(state->argv[state->argc - 1], state->here_doc);
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		exit(handle_error(NULL));
	if (close_fd(&output_fd) == -1 || close_pipes_fds(state) == -1)
		exit(handle_error(NULL));
}

static char	*get_full_cmd_path(t_state *state, char *cmd)
{
	char	*full_cmd_path;
	char	*aux;
	int		i;

	i = 0;
	full_cmd_path = NULL;
	while (state->paths[i])
	{
		aux = full_cmd_path;
		full_cmd_path = ft_strjoin(state->paths[i], cmd);
		if (aux)
			free(aux);
		if (!full_cmd_path)
			exit(handle_error(NULL));
		if (access(full_cmd_path, F_OK) != -1
			&& access(full_cmd_path, X_OK) != -1)
			return (full_cmd_path);
		i++;
	}
	if (full_cmd_path)
		free(full_cmd_path);
	return (NULL);
}

void	execute_command(t_state *state, int cmd_index, int last_cmd_index)
{
	char	*full_cmd_path;
	char	**cmd_args;

	if (cmd_index == FIRST_COMMAND_INDEX + state->here_doc)
		redirect_first_command(state);
	else if (cmd_index > FIRST_COMMAND_INDEX + state->here_doc
		&& cmd_index < last_cmd_index)
		redirect_middle_command(state);
	else if (cmd_index == last_cmd_index)
		redirect_last_command(state);
	cmd_args = ft_split(state->argv[cmd_index], ' ');
	if (!cmd_args)
		exit(handle_error(NULL));
	full_cmd_path = get_full_cmd_path(state, cmd_args[0]);
	if (!full_cmd_path)
		exit(command_not_found_error(cmd_args[0]));
	execve(full_cmd_path, cmd_args, state->envp);
	exit(handle_error(NULL));
}
