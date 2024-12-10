/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:22:01 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/10 13:42:38 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void execute_command(char **envp, char **av)
{
	int success;
	char **path;
	char **cmd;


	// use ft_split() to get aan arr of cmd, arr={"ls", "-l"}
	cmd == ft_split(av, ' ');
	path = get_path(cmd[0], envp);

	success = execve(path, cmd, envp);
	if (success == -1)
		error();

}

