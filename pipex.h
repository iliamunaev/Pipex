/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:22:35 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/17 23:03:23 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// Libraries
# include <errno.h> // errno
# include <stdlib.h> // free, exit
# include <unistd.h> // write, fork, pipe, execve, dup2, close
# include <fcntl.h> // open
# include <stdio.h> // perror
# include <sys/wait.h> // waitpid
# include "libft/libft.h"

// Structures
typedef struct s_pipex
{
	int		fd[2]; // Pipe file descriptors (read and write ends)
	int		infile; // File descriptor for the input file
	int		outfile; // File descriptor for the output file
	char	**envp; // Environment variables
	char	**av; // Command-line arguments
	int		status1; // Exit status for child 1
	int		status2; // Exit status for child 2
	int		argc; // Argument count
}	t_pipex;

typedef struct s_command
{
	char	*cmd; // Command name
	char	**args; // Command arguments
	char	*path; // Full path to the executable
}	t_command;

// pipe creators and executors
void	init_pipex(t_pipex *ctx, int argc, char **argv, char **envp);
void	pipex(t_pipex *ctx);
void	child_1(t_pipex *ctx);
void	child_2(t_pipex *ctx);
void	execute_command(char *av, t_pipex *ctx);
void	cleanup_pipex(t_pipex *ctx);

// error handlers
int		update_exit_status(int status, int update);

// memory leak handlers
void	free_arr_memory(char **paths);

// cmd path finder
char	*get_path(char *cmd, char **envp);
char	**get_path_values(char **envp);
char	*find_command_in_paths(char **paths, char *cmd);

#endif
