/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:22:01 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/11 07:50:31 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

char	**get_path_values(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*path_to_complite;
	int		i;

	paths = get_path_values(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path_to_complite = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path_to_complite, cmd);
		free(path_to_complite);
		if (access(path, F_OK) == 0)
		{
			while (paths[i])
				free(paths[i++]);
			free(paths);
			return (path);
		}
		free(path);
		i++;
	}
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (NULL);
}

void	execute_command(char *av, char **envp)
{
	int		success;
	int		i;
	char	*path;
	char	**cmd;

	cmd = ft_split(av, ' ');
	path = get_path(cmd[0], envp);
	i = 0;
	if (!path)
	{
		while (cmd[i])
		{
			free(cmd[i]);
			i++;
		}
		free(cmd);
		error();
	}
	success = execve(path, cmd, envp);
	if (success == -1)
		error();
}
