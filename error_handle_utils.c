/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:17:54 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/17 21:00:50 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_exit_status(int status, int update)
{
	static int exit_status = 0;

	if (update)
	{
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		else
			exit_status = status;
	}
	return (exit_status);
}

void	error_exit(const char *msg, int status)
{
	if (msg != NULL)
		perror(msg);
	get_exit_status(status, 1);
}

void	program_exit(void)
{
	exit(get_exit_status(0, 0));
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
