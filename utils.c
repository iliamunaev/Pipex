/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:22:01 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/11 09:27:38 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Handles errors by printing an error message and exiting the program.
 *
 * This function uses `perror` to display the last error encountered during
 * a system or library call. After displaying the error message, it terminates
 * the program with a failure status.
 *
 * @return This function does not return as it exits the program.
 */
void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

/**
 * @brief Frees an array of strings allocated dynamically.
 *
 * This static helper function iterates through each string in the `paths` array,
 * frees each individual string, and then frees the array itself.
 *
 * @param paths A null-terminated array of strings to be freed.
 *
 * @note This function should only be used internally within this source file.
 */
static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

/**
 * @brief Searches for the full path of a command within given directories.
 *
 * This static helper function iterates through each directory
 * in the `paths` array, concatenates the directory with the command name
 * to form a potential executable path, and checks if the file exists and
 * is accessible.
 * If a valid path is found, it frees the `paths` array and
 * returns the full path to the executable. If no valid path is found,
 * it frees the `paths` array and returns `NULL`.
 *
 * @param paths An array of directory paths to search within.
 * @param cmd   The command name to locate.
 *
 * @return The full path to the executable if found; otherwise, `NULL`.
 *
 * @note This function should only be used internally within this source file.
 */
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

/**
 * @brief Retrieves the PATH environment variable and splits it
 * into individual directories.
 *
 * This function scans the `envp` array for the `PATH` variable,
 * extracts its value, and splits it into an array of
 * directory paths using the `ft_split` function with ':' as the delimiter.
 *
 * @param envp The environment variables array.
 *
 * @return A dynamically allocated array of directory paths if
 * `PATH` is found and split successfully; otherwise, `NULL`.
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
 * @brief Locates the full path of a command by searching
 * through PATH directories.
 *
 * This function retrieves the PATH directories using
 * `get_path_values`, then uses `find_command_in_paths` to search
 * for the command's executable within those directories.
 * If the executable is found, it returns its full path.
 * Otherwise, it returns `NULL`.
 *
 * @param cmd   The command name to locate (e.g., "ls").
 * @param envp The environment variables array.
 *
 * @return The full path to the executable if found; otherwise, `NULL`.
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
	free_paths(paths);
	return (NULL);
}
