/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:22:35 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/12 17:24:14 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// libs
# include <errno.h>    // errno
# include <stdlib.h>   // free, exit
# include <unistd.h>   // write, fork, pipe, execve, dup2, close
# include <fcntl.h>    // open
# include <stdio.h>    // perror
# include <sys/wait.h> // waitpid
# include "libft/libft.h"

// pipe creators and executors
void	pipex(int f_read, int f_write, char **av, char **envp);
void	child_1(int *fd, int f_read, char **av, char **envp);
void	child_2(int *fd, int f_write, char **av, char **envp);
void	execute_command(char *av, char **envp);

// eeror handlers
void	error_exit(const char *msg, int status);
void	handle_exit_status(int status1, int status2);

// memory leak handlers
void	free_arr_memory(char **paths);

// cmd path finder
char	*get_path(char *cmd, char **envp);
char	**get_path_values(char **envp);
char	*find_command_in_paths(char **paths, char *cmd);

typedef struct s_pipex
{
	pid_t	pid1;	// PID for the first child process
	pid_t	pid2;	// PID for the second child process
	int		pipe_fd[2]; // Pipe file descriptors
	int		infile;	//	Input file descriptor
	int		outfile;	// Output file descriptor
	char	*cmd_path;	// Path of the current command
	char	**cmd_paths;	// Array of all possible command paths
	char	**cmd_args;	// Parsed command arguments
	char	*cmd;	// Current command string
}	t_pipex;

#endif
