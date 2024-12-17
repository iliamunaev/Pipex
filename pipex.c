/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:18:01 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/17 18:35:15 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(char *av, t_pipex *ctx)
{
	t_command cmd;

	if (*av == '\0')
	{
		fprintf(stderr, "Error: Empty command provided.\n");
		exit(EXIT_FAILURE);
	}
	cmd.args = ft_split(av, ' ');
	if (!cmd.args || !cmd.args[0])
	{
		ft_putstr_fd("Command '' not found\n", STDERR_FILENO);
		exit(127);
	}
	cmd.cmd = cmd.args[0];
	cmd.path = get_path(cmd.cmd, ctx->envp);
	if (!cmd.path)
	{
		ft_putstr_fd(cmd.cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		free_arr_memory(cmd.args);
		exit(127);
	}
	if (execve(cmd.path, cmd.args, ctx->envp) == -1)
	{
		perror(cmd.cmd);
		free(cmd.path);
		free_arr_memory(cmd.args);
		if (errno == EACCES)
			exit(126);
		else
			exit(EXIT_FAILURE);
	}
}

void	child_1(t_pipex *ctx)
{
	if (dup2(ctx->infile, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(ctx->fd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (ctx->fd[0] >= 0)
		close(ctx->fd[0]);
	execute_command(ctx->av[2], ctx);
}

void	child_2(t_pipex *ctx)
{

	if (dup2(ctx->fd[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(ctx->outfile, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (ctx->fd[1] >= 0)
		close(ctx->fd[1]);
	execute_command(ctx->av[3], ctx);
}

void    pipex(t_pipex *ctx)
{
    pid_t	pid_child1;
	pid_t	pid_child2;

    pid_child1 = fork();
    if (pid_child1 == -1)
    {
        error_exit("Fork failed for child 1", EXIT_FAILURE);
        //foo();
    }
    if (pid_child1 == 0)
        child_1(ctx);
    pid_child2 = fork();
    if (pid_child2 == -1)
    {
        error_exit("Fork failed for child 2", EXIT_FAILURE);
       // foo();
    }
    if (pid_child2 == 0)
        child_2(ctx);
    close(ctx->fd[0]);
    close(ctx->fd[1]);


   	waitpid(pid_child1, &ctx->status1, 0);
   	waitpid(pid_child2, &ctx->status2, 0);
	get_exit_status(ctx->status2, 1);
}

void    init_pipex(t_pipex *ctx, int argc, char **argv, char **envp)
{
    if (argc != 5)
    {
		ft_putstr_fd("Invalid number of arguments\n", STDERR_FILENO); // tested
        exit(EXIT_FAILURE);
    }

    ctx->argc = argc;
    ctx->av = argv;
    ctx->envp = envp;

    ctx->infile = open(argv[1], O_RDONLY);
	if (ctx->infile == -1)
	{
		if (errno == ENOENT)
			error_exit(argv[1], EXIT_FAILURE); // "No such file or directory"
		if (errno == EACCES)
        {
			error_exit(argv[1], EXIT_FAILURE); // Exit code 126
        }
	}

    ctx->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (ctx->outfile == -1)
	{
		if (errno == EACCES)
            error_exit(argv[4], 126);
        error_exit(argv[4], EXIT_FAILURE);
	}
    if (pipe(ctx->fd) == -1)
        error_exit("Pipe creation failed", EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
    t_pipex ctx;

    init_pipex(&ctx, argc, argv, envp);
    pipex(&ctx);
    cleanup_pipex(&ctx);
    program_exit();
}
