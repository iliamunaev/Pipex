/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:22:01 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/17 23:41:24 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	execute_command(char *av, t_pipex *ctx)
{
	t_command	cmd;

	cmd.args = ft_split(av, ' ');
	if (!cmd.args || !cmd.args[0])
		perror_n_exit("Command '' not found\n", 127);
	cmd.cmd = cmd.args[0];
	cmd.path = get_path(cmd.cmd, ctx->envp);
	if (!cmd.path)
	{
		perror(cmd.cmd);
		free_arr_memory(cmd.args);
		perror_n_exit(": command not found\n", 127);
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
