/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:17:54 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/12 16:18:06 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(const char *msg, int status)
{
	if (msg != NULL)
		perror(msg);
	exit(status);
}

void	handle_exit_status(int status1, int status2)
{
	if (WIFEXITED(status2))
		exit(WEXITSTATUS(status2));
	else if (WIFEXITED(status1))
		exit(WEXITSTATUS(status1));
}
