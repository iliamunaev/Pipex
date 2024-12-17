/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:17:54 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/17 23:43:49 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exit_status(int status)
{
	int	exit_status;

	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else
		exit_status = status;
	return (exit_status);
}

int	perror_n_exit(char *msg, int e)
{
	if (msg)
		perror(msg);
	exit(e);
}

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

void	free_arr_memory(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
