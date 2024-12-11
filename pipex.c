/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:18:01 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/11 08:31:47 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_1(int *fd, int f_read, char **av, char **envp)
{
	if (dup2(f_read, STDIN_FILENO) == -1)
		error();
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error();
	close (fd[0]);
	execute_command(av[2], envp);
}

void	child_2(int *fd, int f_write, char **av, char **envp)
{
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error();
	if (dup2(f_write, STDOUT_FILENO) == -1)
		error();
	close (fd[1]);
	execute_command(av[3], envp);
}

void	pipex(int f_read, int f_write, char **av, char **envp)
{
	int		fd[2];
	pid_t	child1;
	pid_t	child2;

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
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	int	f_read;
	int	f_write;

	if (ac != 5)
		error();
	if (*av[2] == '\0' || *av[3] == '\0')
		error();
	f_read = open(av[1], O_RDONLY);
	if (f_read == -1)
		error();
	f_write = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (f_write == -1)
		error();
	pipex(f_read, f_write, av, envp);
	return (0);
}
