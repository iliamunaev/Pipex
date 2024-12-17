/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:17:54 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/17 23:46:57 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Retrieves the exit status of a process.
 *
 * If the process exited normally, it returns the exit code.
 * Otherwise, it returns the raw status code.
 *
 * @param status The status code returned by waitpid.
 * @return The processed exit status.
 */
int	exit_status(int status)
{
	int	exit_status;

	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else
		exit_status = status;
	return (exit_status);
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
