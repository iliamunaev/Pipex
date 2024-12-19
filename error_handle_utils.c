/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:17:54 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/19 15:30:24 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * exit_status - Determines the exit status of a child process.
 *
 * This function analyzes the status of a child process to determine
 * the exit code. If the process exited normally, it returns the exit
 * code using WEXITSTATUS. Otherwise, it returns the signal number
 * that caused the termination using WTERMSIG.
 *
 * @status: The status returned by waitpid() or wait().
 *
 * Return: The exit code if the process exited normally, or the signal
 * number if it was terminated by a signal.
 */
int	exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (WTERMSIG(status));
}

/**
 * @brief Prints an error message and exits the program.
 *
 * Uses perror to print the provided message, and exits with
 * the given exit code.
 *
 * @param msg The error message to display.
 * @param e   The exit code to terminate the program with.
 */
int	perror_n_exit(char *msg, int e)
{
	if (msg)
		perror(msg);
	exit(e);
}

int	pcustom_error_n_exit(char *msg1, char *msg2, int e)
{
	if (msg1)
		ft_putstr_fd(msg1, STDERR_FILENO);
	if (msg2)
		ft_putstr_fd(msg2, STDERR_FILENO);
	exit(e);
}

/**
 * @brief Cleans up file descriptors in the pipex context.
 *
 * Closes the infile, outfile, and pipe file descriptors
 * if they are open (greater than zero).
 *
 * @param ctx The pipex context containing file descriptors.
 */
void	cleanup_pipex(t_pipex *ctx)
{
	if (ctx->infile > 0)
		close(ctx->infile);
	if (ctx->outfile > 0)
		close(ctx->outfile);
	if (ctx->fd[0] > 0)
		close(ctx->fd[0]);
	if (ctx->fd[1] > 0)
		close(ctx->fd[1]);
}

/**
 * @brief Frees memory allocated for a string array.
 *
 * Iterates through a null-terminated array of strings,
 * freeing each string, and then frees the array itself.
 *
 * @param arr A null-terminated array of dynamically allocated strings.
 */
void	free_arr_memory(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
