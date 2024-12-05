#ifndef PIPEX_H
# define PIPEX_H

#include <fcntl.h> // open()
#include <errno.h> // perror()
#include <unistd.h> // close(), dup2(), pipe(), fork()
#include <sys/wait.h> // waitpid()

void	error(void);
void child_p(int *fd; char **av, char **envp);
void parent_p(int *fd; char **av, char **envp);

#endif // PIPEX_H
