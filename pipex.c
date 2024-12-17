/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:18:01 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/17 20:58:10 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	pipex(t_pipex *ctx)
{
	pid_t	pid_child1;
	pid_t	pid_child2;

	pid_child1 = fork();
	if (pid_child1 == -1)
		error_exit("Fork failed for child 1", EXIT_FAILURE);
	if (pid_child1 == 0)
		child_1(ctx);
	pid_child2 = fork();
	if (pid_child2 == -1)
		error_exit("Fork failed for child 2", EXIT_FAILURE);
	if (pid_child2 == 0)
		child_2(ctx);
	close(ctx->fd[0]);
	close(ctx->fd[1]);
	waitpid(pid_child1, &ctx->status1, 0);
	waitpid(pid_child2, &ctx->status2, 0);
	get_exit_status(ctx->status2, 1);
}

void	init_pipex(t_pipex *ctx, int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		ft_putstr_fd("Invalid number of arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	ctx->argc = argc;
	ctx->av = argv;
	ctx->envp = envp;
	ctx->infile = open(argv[1], O_RDONLY);
	if (ctx->infile == -1)
	{
		if (errno == ENOENT)
			error_exit(argv[1], EXIT_FAILURE);
		if (errno == EACCES)
			error_exit(argv[1], EXIT_FAILURE);
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
	t_pipex	ctx;

	init_pipex(&ctx, argc, argv, envp);
	pipex(&ctx);
	cleanup_pipex(&ctx);
	program_exit();
}
