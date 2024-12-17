/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:18:01 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/17 23:00:22 by imunaev-         ###   ########.fr       */
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
	if (*ctx->av[2] == '\0')
	{
		perror("Error: Empty command provided.\n");
		exit(EXIT_FAILURE);
	}
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
	if (*ctx->av[3] == '\0')
	{
		perror("Error: Empty command provided.\n");
		exit(EXIT_FAILURE);
	}
	execute_command(ctx->av[3], ctx);
}

void	pipex(t_pipex *ctx)
{
	pid_t	pid_child1;
	pid_t	pid_child2;

	pid_child1 = fork();
	if (pid_child1 == -1)
	{
		perror("Fork failed for child 1");
		exit(EXIT_FAILURE);
	}
	if (pid_child1 == 0)
		child_1(ctx);
	pid_child2 = fork();
	if (pid_child2 == -1)
	{
		perror("Fork failed for child 2");
		exit(EXIT_FAILURE);
	}
	if (pid_child2 == 0)
		child_2(ctx);
	close(ctx->fd[0]);
	close(ctx->fd[1]);
	waitpid(pid_child1, &ctx->status1, 0);
	waitpid(pid_child2, &ctx->status2, 0);
	update_exit_status(ctx->status2, 1);
}

void	init_pipex(t_pipex *ctx, int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		perror("Invalid number of arguments\n");
		exit(EXIT_FAILURE);
	}
	ctx->argc = argc;
	ctx->av = argv;
	ctx->envp = envp;
	ctx->infile = open(argv[1], O_RDONLY);
	if (ctx->infile == -1)
			perror(argv[1]);
	ctx->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ctx->outfile == -1)
	{
		if (errno == EACCES)
		{
			perror(argv[4]);
			update_exit_status(126, 1);
		}
	}
	if (pipe(ctx->fd) == -1)
	{
		perror("Pipe creation failed");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	ctx;

	init_pipex(&ctx, argc, argv, envp);
	pipex(&ctx);
	cleanup_pipex(&ctx);
	exit(update_exit_status(0, 0));
}
