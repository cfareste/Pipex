/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:55:26 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/04/09 20:19:06 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# define DEFAULT_ERROR "pipex"
# define ERROR_PREFIX "pipex: "
# define PATH_PREFIX "PATH="
# define DEFAULT_PATH "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
# define FIRST_COMMAND_INDEX 2
# define HERE_DOC "here_doc"
# define HERE_DOC_PREFIX "> "
# define HERE_DOC_INDEX 1

// Structs
typedef struct s_state
{
	pid_t	pid;
	int		argc;
	char	**argv;
	char	**envp;
	int		pipe_fds[2];
	char	**paths;
	int		status;
	int		here_doc;
	int		here_doc_fd;
	char	*limiter;
}	t_state;

// Sructs helpers
int		init_state(t_state *state, int argc, char **argv, char **envp);
void	free_state(t_state *state);
int		close_pipes_fds(t_state *state);

// Commands helpers
void	execute_command(t_state *state, int cmd_index, int last_cmd_index);

// FD Helpers
int		open_input_file(char *file_path);
int		open_output_file(char *file_path, int has_here_doc);
int		close_fd(int *fd);

// Here_doc helpers
int		has_here_doc(char *argument);
int		read_from_here_doc(t_state *state);

// Error handlers
int		custom_error(char *error);
int		command_not_found_error(char *cmd);
int		handle_error(char *error);

#endif
