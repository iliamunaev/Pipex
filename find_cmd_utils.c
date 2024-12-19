/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:22:01 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/19 15:17:49 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Searches for the full path of a command in a list of directories.
 *
 * Iterates through each directory in the paths array, concatenates the command,
 * and checks if the resulting path exists and is accessible.
 *
 * @param paths A null-terminated array of directory paths.
 * @param cmd   The command to search for (e.g., "ls").
 * @return The full path to the command if found, otherwise NULL.
 */
char	*find_command_in_paths(char **paths, char *cmd)
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
			free_arr_memory(paths);
			return (path);
		}
		free(path);
		i++;
	}
	return (NULL);
}

/**
 * @brief Retrieves and splits the PATH environment variable into directories.
 *
 * Scans the environment variables for the PATH variable, extracts its value,
 * and splits it into an array of directory paths using ':' as the delimiter.
 *
 * @param envp The environment variables array.
 * @return A null-terminated array of directories, or NULL if PATH is not found.
 */
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

/**
 * @brief Retrieves the full path of a command
 * using the PATH environment variable.
 *
 * This function retrieves the PATH environment variable,
 * splits it into directories,
 * and searches for the executable command within those directories.
 *
 * @param cmd  The command to search for (e.g., "ls").
 * @param envp The environment variables array.
 * @return The full path to the command if found, otherwise NULL.
 */
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
	free_arr_memory(paths);
	return (NULL);
}
