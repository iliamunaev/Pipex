/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:17:54 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/17 12:33:05 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * Maintains and retrieves the program's exit status.
 */
int	get_exit_status(int status, int update)
{
	static int exit_status = 0;

	if (update)
	{
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status); // Exit code if process exited normally
		else
			exit_status = status; // Raw status if abnormal termination
	}
	return (exit_status);
}

/*
 * Handles the exit status from two processes.
 */
void	handle_exit_status(int status1, int status2)
{
	if (WIFEXITED(status2))
		get_exit_status(status2, 1); // Update with status2
	else if (WIFEXITED(status1))
		get_exit_status(status1, 1); // Update with status1
}

/*
 * Prints an error message and exits the program with a given status.
 */
void	error_exit(const char *msg, int status)
{
	if (msg != NULL)
		perror(msg); // Prints the system error message to stderr
	get_exit_status(status, 1); // Update exit status
	exit(get_exit_status(0, 0)); // Exit with the updated status
}

/*
 * Exits the program with the currently maintained exit status.
 */
void	program_exit(void)
{
	exit(get_exit_status(0, 0)); // Retrieve the exit status and exit
}

/*
 * Dummy function for testing or placeholder purposes.
 */
void	foo(void)
{
	return ;
}
