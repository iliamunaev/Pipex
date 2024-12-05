/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:18:01 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/05 16:09:40 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int main(int ac, char **av)
{
    int	fd_read;
    int	fd_write;
    int pipe_fd[2];
    pid_t child_1;
    pid_t child_2;

    if (ac != 5)
    {
        fprintf(stderr, "Usage: %s infile cmd1 cmd2 outfile\n", av[0]);
        return (1);
    }

    // Open files
    if (!open_files(&fd_read, &fd_write, av))
        return (2);

    // Create the pipe
    if (pipe(pipe_fd) == -1)
    {
        perror("Error creating pipe");
        close_all(fd_read, fd_write, -1, -1);
        return (3);
    }

    // First child: Execute cmd1
    if (create_child(&child_1, fd_read, fd_write, pipe_fd))
    {
        if (child_1 == 0)
        {
            // Close unused pipe end
            close(pipe_fd[0]);
            if (dup_and_close(fd_read, pipe_fd[1]))
            {
                execlp(av[2], av[2], NULL);
                perror("Error executing cmd1");
                exit(4);
            }
            else
            {
                perror("Error duplicating file descriptors in first child");
                exit(4);
            }
        }
    }

    // Second child: Execute cmd2
    if (create_child(&child_2, fd_read, fd_write, pipe_fd))
    {
        if (child_2 == 0)
        {
            // Close unused pipe end
            close(pipe_fd[1]);
            if (dup_and_close(pipe_fd[0], fd_write))
            {
                execlp(av[3], av[3], NULL);
                perror("Error executing cmd2");
                exit(5);
            }
            else
            {
                perror("Error duplicating file descriptors in second child");
                exit(5);
            }
        }
    }

    // Parent process
    close_all(fd_read, fd_write, pipe_fd[0], pipe_fd[1]);

    // Wait for both children
    waitpid(child_1, NULL, 0);
    waitpid(child_2, NULL, 0);

    printf("Program completed successfully\n");
    return (0);
}
