/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:18:01 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/19 14:44:45 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Executes the first child process.
 *
 * Redirects stdin to infile and stdout to the pipe write end.
 * Closes unnecessary file descriptors and executes the first command.
 *
 * @param ctx The pipex context containing file descriptors and arguments.
 */
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
		ft_putstr_fd(" : command not found\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	close(ctx->fd[0]);
	execute_command(ctx->av[2], ctx);
}

/**
 * @brief Executes the second child process.
 *
 * Redirects stdin to the pipe read end and stdout to outfile.
 * Closes unnecessary file descriptors and executes the second command.
 *
 * @param ctx The pipex context containing file descriptors and arguments.
 */

void	child_2(t_pipex *ctx)
{
	if (dup2(ctx->fd[0], STDIN_FILENO) == -1)
		perror_n_exit("dup2 stdin failed in child2", EXIT_FAILURE);
	if (ctx->outfile != -1)
	{
		if (dup2(ctx->outfile, STDOUT_FILENO) == -1)
			perror_n_exit("dup2 stdout failed in child2", EXIT_FAILURE);
	}
	else
	{
		if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
			perror_n_exit("dup2 failed in child2", EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
	if (ctx->fd[1] >= 0)
		close(ctx->fd[1]);
	if (*ctx->av[3] == '\0')
	{
		ft_putstr_fd(" : command not found\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	execute_command(ctx->av[3], ctx);
}

/**
 * @brief Manages the pipex process flow.
 *
 * Forks two child processes to execute two commands in a pipeline.
 * Closes unused file descriptors and waits for both child processes.
 *
 * @param ctx The pipex context containing file descriptors and arguments.
 * @return The exit status of the second child process.
 */
int	pipex(t_pipex *ctx)
{
	pid_t	pid_child1;
	pid_t	pid_child2;

	pid_child1 = fork();
	if (pid_child1 == -1)
	{
		ft_putstr_fd("Fork failed for child 1\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (pid_child1 == 0)
		child_1(ctx);
	pid_child2 = fork();
	if (pid_child2 == -1)
	{
		ft_putstr_fd("Fork failed for child 2\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (pid_child2 == 0)
		child_2(ctx);
	close(ctx->fd[0]);
	close(ctx->fd[1]);
	waitpid(pid_child1, &ctx->status1, 0);
	waitpid(pid_child2, &ctx->status2, 0);
	return (exit_status(ctx->status2));
}

/**
 * @brief Initializes the pipex context.
 *
 * Validates arguments, opens infile and outfile, and creates a pipe.
 * Handles errors for invalid arguments, file operations, and pipe creation.
 *
 * @param ctx  The pipex context to initialize.
 * @param argc The argument count.
 * @param argv The argument vector.
 * @param envp The environment variables.
 */
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
		perror(argv[1]);
	}
	ctx->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ctx->outfile == -1)
	{
		if (errno == EACCES)
			perror(argv[4]);
		ctx->outfile = -1;
	}
	if (pipe(ctx->fd) == -1)
		perror_n_exit("Pipe creation faield", EXIT_FAILURE);
}

/**
 * @brief The entry point of the pipex program.
 *
 * Initializes the pipex context, manages the pipeline execution,
 * cleans up resources, and exits with the appropriate status code.
 *
 * @param argc The argument count.
 * @param argv The argument vector.
 * @param envp The environment variables.
 * @return Returns the exit status of the second child process.
 */
int	main(int argc, char **argv, char **envp)
{
	t_pipex	ctx;
	int		status;

	init_pipex(&ctx, argc, argv, envp);
	status = pipex(&ctx);
	cleanup_pipex(&ctx);
	exit(exit_status(status));
}
