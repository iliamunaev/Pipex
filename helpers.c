/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:17:39 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/05 16:09:54 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

int close_all(int fd1, int fd2, int fd3, int fd4)
{
    int fds[4] = {fd1, fd2, fd3, fd4};
    for (int i = 0; i < 4; i++)
    {
        if (fds[i] != -1 && close(fds[i]) == -1)
        {
            perror("Error closing file descriptor");
            return (1);
        }
    }
    return (0);
}

int is_opened(int fd)
{
    if (fd == -1)
    {
        perror("Error opening file descriptor");
        return (0);
    }
    return (1);
}

int open_files(int *fd_read, int *fd_write, char **av)
{
    *fd_read = open(av[1], O_RDONLY);
    *fd_write = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (!is_opened(*fd_read) || !is_opened(*fd_write))
    {
        close_all(*fd_read, *fd_write, -1, -1);
        return (0);
    }
    return (1);
}

int create_child(pid_t *child, int fd_read, int fd_write, int *pipe_fd)
{
    *child = fork();
    if (*child == -1)
    {
        perror("Error forking child");
        close_all(fd_read, fd_write, pipe_fd[0], pipe_fd[1]);
        return (0);
    }
    return (1);
}

int dup_and_close(int fd_in, int fd_out)
{
    if (dup2(fd_in, STDIN_FILENO) == -1 || dup2(fd_out, STDOUT_FILENO) == -1)
    {
        perror("Error duplicating file descriptors");
        return (0);
    }
    close_all(fd_in, fd_out, -1, -1);
    return (1);
}
