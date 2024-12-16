/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:17:54 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/15 22:04:48 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
void	error_exit(const char *msg, int status)
{
	if (msg != NULL)
		perror(msg);
	exit(status);
}*/
#include <stdio.h> ////////////////////////////////////////////////////////////////////////

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
	printf("TEST exit_status: %d\n", exit_status);

	return (exit_status);
}

void	handle_exit_status(int status1, int status2) {
	if (WIFEXITED(status2))
		get_exit_status(status2, 1); // Update with status2
	else if (WIFEXITED(status1))
		get_exit_status(status1, 1); // Update with status1
}

void	error_exit(const char *msg, int status) {
	if (msg != NULL)
		perror(msg);
	get_exit_status(status, 1); // Update exit status with error code
}

void	program_exit(void)
{
	exit(get_exit_status(0, 0)); // Retrieve the exit status and exit
}

void foo(void)
{
	return ;
}
