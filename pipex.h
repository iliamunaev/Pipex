/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imunaev- <imunaev-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:48:15 by imunaev-          #+#    #+#             */
/*   Updated: 2024/12/11 08:48:49 by imunaev-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h> // open()
# include <errno.h> // perror()
# include <unistd.h> // close(), dup2(), pipe(), fork()
# include <sys/wait.h> // waitpid()
# include <stdlib.h> // EXIT_FAILURE
# include <stdio.h> // perror()
# include "libft/libft.h"

void	child_1(int *fd, int f_read, char **av, char **envp);
void	child_2(int *fd, int f_write, char **av, char **envp);
void	pipex(int f_read, int f_write, char **av, char **envp);
void	error(void);
char	**get_path_values(char **envp);
char	*get_path(char *cmd, char **envp);
void	execute_command(char *av, char **envp);

#endif // PIPEX_H
