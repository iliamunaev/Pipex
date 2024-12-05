/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:18:01 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/05 18:21:33 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void child_p(int *fd; char **av, char **envp)
{
	int	file_read;

	file_read = open(av[1], O_RDONLY);
	if (file_read == -1)
		error();
	if(dup2(file_read, STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
		error();
	close(fd[0]);
	execute(av[2], envp);
}

void parent_p(int *fd; char **av, char **envp)
{
	int	file_write;

	file_write = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);  // 0644??
	if (file_write == -1)
		error();
	if(dup2(fd[0], STDIN_FILENO) == -1 || dup2(file_write, STDOUT_FILENO) == -1)
		error();
	close(fd[1]);
	execute(av[3], envp);
}

int	main(int ac, char **av)
{
	int	fd[2];
	pid_t pid;

	if(ac != 5)
		error();

	if(pipe(fd) == -1)
		error();

	pid = fork();

	if(pid == -1)
		error();

	if(pid == 0)
		child_p(av, envp, fd);

	waitpid(pid, NULL, 0);
	parent_p(av, envp, fd);

	return (0);
}
