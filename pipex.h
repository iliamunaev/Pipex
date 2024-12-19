/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:22:35 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/19 15:25:17 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// Libraries
# include <errno.h>		// errno
# include <stdlib.h>	// free, exit
# include <unistd.h>	// write, fork, pipe, execve, dup2, close
# include <fcntl.h>		// open
# include <stdio.h>		// perror
# include <sys/wait.h>	// waitpid
# include "libft/libft.h"

// Structures
/**
 * @brief Represents the main context for the pipex program.
 *
 * Contains all necessary data for managing pipes, file descriptors,
 * environment variables, and command-line arguments.
 *
 * Fields:
 * - `fd[2]`:   Pipe file descriptors (`fd[0]` for reading, `fd[1]` for writing).
 * - `infile`:  File descriptor for the input file,
 *              used as input to the first command.
 * - `outfile`: File descriptor for the output file, used for the final output.
 * - `envp`:    Array of strings representing environment variables.
 * - `av`:      Array of strings representing the command-line arguments.
 * - `status1`: Exit status of the first child process.
 * - `status2`: Exit status of the second child process.
 * - `argc`:    The total number of command-line arguments.
 */
typedef struct s_pipex
{
	int		fd[2];
	int		infile;
	int		outfile;
	char	**envp;
	char	**av;
	int		status1;
	int		status2;
	int		argc;
}	t_pipex;

/**
 * @brief Represents an individual command.
 *
 * Includes its name, arguments, and resolved executable path.
 *
 * Fields:
 * - `cmd`:  The name of the command.
 * - `args`: Array of strings representing arguments to the command.
 * - `path`: The full path to the command's executable.
 */
typedef struct s_command
{
	char	*cmd;
	char	**args;
	char	*path;
}	t_command;

// Functions
// pipe creators and executors
void	init_pipex(t_pipex *ctx, int argc, char **argv, char **envp);
int		pipex(t_pipex *ctx);
void	child_1(t_pipex *ctx);
void	child_2(t_pipex *ctx);
void	execute_command(char *av, t_pipex *ctx);

// error handlers
int		exit_status(int status);
int		perror_n_exit(char *msg, int e);
int		pcustom_error_n_exit(char *msg1, char *msg2, int e);

// memory leak handlers
void	free_arr_memory(char **paths);
void	cleanup_pipex(t_pipex *ctx);

// cmd path finder
char	*get_path(char *cmd, char **envp);
char	**get_path_values(char **envp);
char	*find_command_in_paths(char **paths, char *cmd);

// cmd executors
void	parse_and_resolve_command(char *av, t_pipex *ctx, t_command *cmd);
void	execute_resolved_command(t_command *cmd, t_pipex *ctx);
void	execute_command(char *av, t_pipex *ctx);

#endif
