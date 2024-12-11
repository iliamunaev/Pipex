/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:22:01 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/11 09:07:20 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

static char	*find_command_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*path;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
		{
			free_paths(paths);
			return (path);
		}
		free(path);
		i++;
	}
	return (NULL);
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

	paths = get_path_values(envp);
	if (!paths)
		return (NULL);
	path = find_command_in_paths(paths, cmd);
	if (path)
		return (path);
	free_paths(paths);
	return (NULL);
}
