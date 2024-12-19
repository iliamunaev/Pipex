/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:16:25 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/19 15:29:28 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Executes the resolved command using execve.
 *
 * Uses execve to execute the command specified in cmd->path
 * with its arguments and environment variables. If execve fails, it frees
 * allocated memory for cmd->path and cmd->args, and exits with an appropriate
 * error code. EACCES results in exit code 126, while other errors exit with
 * EXIT_FAILURE.
 *
 * @cmd: A pointer to the t_command structure containing command details.
 * @ctx: A pointer to the t_pipex structure containing the execution context.
  */
void	execute_resolved_command(t_command *cmd, t_pipex *ctx)
{
	if (execve(cmd->path, cmd->args, ctx->envp) == -1)
	{
		free(cmd->path);
		free_arr_memory(cmd->args);
		if (errno == EACCES)
			exit(126);
		else
			exit(EXIT_FAILURE);
	}
}
/**
 * @brief Parses the input and resolves the command path.
 *
 * Splits the input argument string into an array of arguments
 * using ft_split. It determines whether the command includes a direct path
 * (contains '/') or resolves its path using the system PATH. If the command
 * cannot be resolved, it outputs an error message and exits with code 127.
 *
 * @av: The command-line argument string containing the command to execute.
 * @ctx: A pointer to the t_pipex structure containing the execution context.
 * @cmd: A pointer to the t_command structure to
 * store the parsed and resolved command.
 */

void	parse_and_resolve_command(char *av, t_pipex *ctx, t_command *cmd)
{
	cmd->args = ft_split(av, ' ');
	if (!cmd->args || !cmd->args[0])
		pcustom_error_n_exit(cmd->args[0], " : command not found\n", 127);
	cmd->cmd = cmd->args[0];
	if (ft_strchr(cmd->cmd, '/'))
		cmd->path = ft_strdup(cmd->cmd);
	else
	{
		cmd->path = get_path(cmd->cmd, ctx->envp);
		if (!cmd->path)
		{
			ft_putstr_fd(cmd->cmd, STDERR_FILENO);
			free_arr_memory(cmd->args);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			exit(127);
		}
	}
}

/**
 * @brief Parses, resolves, and executes a command.
 *
 * TOrchestrates the process of parsing the command-line argument,
 * resolving the command path, and executing the command. It uses
 * parse_and_resolve_command to handle parsing and path resolution, and
 * execute_resolved_command to perform the execution.
 *
 * @av: The command-line argument string containing the command to execute.
 * @ctx: A pointer to the t_pipex structure containing the execution context.
 */
void	execute_command(char *av, t_pipex *ctx)
{
	t_command	cmd;

	parse_and_resolve_command(av, ctx, &cmd);
	execute_resolved_command(&cmd, ctx);
}
