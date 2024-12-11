/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:18:01 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/11 23:00:06 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Executes a command by parsing the input string,
 * locating the executable path, and invoking it with execve.
 *
 * @param av   The command string to execute (e.g., "ls -l").
 * @param envp The environment variables.
 *
 * This function splits the command string into arguments,
 * finds the full path to the executable, and then uses execve
 * to execute the command. If any step fails, it
 * handles the error appropriately.
 */
void	execute_command(char *av, char **envp)
{
	char	*path;
	char	**cmd;
	char	*command_name;
	int		i;

	cmd = ft_split(av, ' ');
	if (!cmd || !cmd[0])
		error_exit("Invalid command", 127);
	path = get_path(cmd[0], envp);
	command_name = ft_strdup(cmd[0]);
	i = 0;
	if (!path)
	{
		while (cmd[i])
		{
			free(cmd[i]);
			i++;
		}
		free(cmd);
		free(command_name);
		exit(127);
	}
	i = 0;
	if (execve(path, cmd, envp) == -1)
	{
		perror("execve failed");
		free(path);
		free(command_name);
		while (cmd[i])
		{
			free(cmd[i]);
			i++;
		}
		free(cmd);
		exit(127);
	}
}

/**
 * @brief Handles the first child process in the pipex setup.
 *
 * @param fd      The file descriptors for the pipe.
 * @param f_read  The file descriptor for reading input.
 * @param av      The array of command-line arguments.
 * @param envp    The environment variables.
 *
 * This function sets up the standard input and output
 * for the first child process,
 * closes unnecessary file descriptors, and executes the first command.
 */
void	child_1(int *fd, int f_read, char **av, char **envp)
{
	if (dup2(f_read, STDIN_FILENO) == -1)
		error();
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error();
	close (fd[0]);
	execute_command(av[2], envp);
}

/**
 * @brief Handles the second child process in the pipex setup.
 *
 * @param fd       The file descriptors for the pipe.
 * @param f_write  The file descriptor for writing output.
 * @param av       The array of command-line arguments.
 * @param envp     The environment variables.
 *
 * This function sets up the standard input and output
 * for the second child process,
 * closes unnecessary file descriptors, and
 * executes the second command.
 */
void	child_2(int *fd, int f_write, char **av, char **envp)
{
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error();
	if (dup2(f_write, STDOUT_FILENO) == -1)
		error();
	close (fd[1]);
	execute_command(av[3], envp);
}

/**
 * @brief Sets up the piping between two child processes to execute two commands.
 *
 * @param f_read  The file descriptor for reading input.
 * @param f_write The file descriptor for writing output.
 * @param av      The array of command-line arguments.
 * @param envp    The environment variables.
 *
 * This function creates a pipe, forks two child processes, and
 * assigns the appropriate
 * standard input and output for each child.
 * It then waits for both children to finish.
 */
void	pipex(int f_read, int f_write, char **av, char **envp)
{
	int		fd[2];
	pid_t	child1;
	pid_t	child2;
	int		status1;
	int		status2;

	if (pipe(fd) == -1)
		error();
	child1 = fork();
	if (child1 == -1)
		error();
	if (child1 == 0)
		child_1(fd, f_read, av, envp);
	child2 = fork();
	if (child2 == -1)
		error();
	if (child2 == 0)
		child_2(fd, f_write, av, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(child1, &status1, 0);
	waitpid(child2, &status2, 0);
	handle_exit_status(status1, status2);
}

/**
 * @brief The main entry point of the pipex program.
 *
 * @param ac    The argument count.
 * @param av    The argument vector.
 * @param envp  The environment variables.
 *
 * This function validates the command-line arguments,
 * opens the input and output files, and initiates
 * the piping process between the two commands.
 *
 * Usage:
 *   ./pipex infile "cmd1" "cmd2" outfile
 */
int	main(int ac, char **av, char **envp)
{
	int	f_read;
	int	f_write;

	if (ac != 5)
		error();
	if (*av[2] == '\0' || *av[3] == '\0')
		error_exit("Error opening input file", 1);
	f_read = open(av[1], O_RDONLY);
	f_write = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (f_read == -1 || f_write == -1)
	{
		if (f_read == -1)
		{
			if (errno == EACCES)
				error_exit(av[1], 0);
			error_exit(av[1], 1);
		}
		if (f_write == -1)
			error_exit("Error opening output file", 1);
	}
	pipex(f_read, f_write, av, envp);
	return (0);
}
