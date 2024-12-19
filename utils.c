/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:22:01 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/19 15:01:35 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Parses and executes a command using execve.
 *
 * Splits the command string into arguments,
 * retrieves the full path of the command,
 * and executes it using execve.
 * Handles errors such as missing commands or permission issues.
 *
 * @param av  The command string (e.g., "ls -l").
 * @param ctx The pipex context containing the environment variables.
 */
void	execute_command(char *av, t_pipex *ctx)
{
	t_command	cmd;

	cmd.args = ft_split(av, ' ');
	if (!cmd.args || !cmd.args[0])
		pcustom_error_n_exit(cmd.args[0], " : command not found\n", 127);
	cmd.cmd = cmd.args[0];
	if (ft_strchr(cmd.cmd, '/'))
		cmd.path = ft_strdup(cmd.cmd);
	else
	{
		cmd.path = get_path(cmd.cmd, ctx->envp);
		if (!cmd.path)
		{
			ft_putstr_fd(cmd.cmd, STDERR_FILENO);
			free_arr_memory(cmd.args);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			exit(127);
		}
	}
	if (execve(cmd.path, cmd.args, ctx->envp) == -1)
	{
		free(cmd.path);
		free_arr_memory(cmd.args);
		if (errno == EACCES)
			exit(126);
		else
			exit(EXIT_FAILURE);
	}
}

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
