#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h> // ---------------------- delete
#include <fcntl.h> // open()
#include <errno.h> // perror()
#include <string.h> // strerror()
#include <unistd.h> // close(), dup2(), pipe(), fork()
#include <sys/wait.h> // waitpid()

int	check_open(int fd);

#endif // PIPEX_H
