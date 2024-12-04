#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

// Error handling utility
void error_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

// Count the number of arguments in a command string
int count_args(const char *cmd)
{
    int count = 0;
    int in_word = 0;

    while (*cmd)
    {
        if (*cmd != ' ' && !in_word)
        {
            in_word = 1;
            count++;
        }
        else if (*cmd == ' ')
            in_word = 0;
        cmd++;
    }
    return count;
}

// Parse the command string into arguments
char **parse_command(const char *cmd)
{
    int i = 0, j = 0, k = 0, num_args = count_args(cmd);
    char **args = malloc((num_args + 1) * sizeof(char *));
    if (!args)
        error_exit("malloc");

    while (*cmd)
    {
        if (*cmd != ' ')
        {
            // Allocate memory for the argument
            k = 0;
            const char *start = cmd;
            while (*cmd && *cmd != ' ')
            {
                k++;
                cmd++;
            }
            args[i] = malloc((k + 1) * sizeof(char));
            if (!args[i])
                error_exit("malloc");
            strncpy(args[i], start, k);
            args[i][k] = '\0';
            i++;
        }
        else
            cmd++;
    }
    args[i] = NULL;
    return args;
}

// Free the parsed arguments
void free_args(char **args)
{
    for (int i = 0; args[i]; i++)
        free(args[i]);
    free(args);
}

// Execute a command
void execute_command(const char *cmd, char **envp)
{
    char **args = parse_command(cmd);

    if (execve(args[0], args, envp) == -1)
    {
        perror("execve");
        free_args(args);
        exit(EXIT_FAILURE);
    }
    free_args(args);
}

int main(int argc, char *argv[], char *envp[])
{
    int fd_in, fd_out, pipe_fd[2];
    pid_t child1, child2;

    if (argc != 5)
    {
        write(STDERR_FILENO, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
        exit(EXIT_FAILURE);
    }

    // Open input file
    fd_in = open(argv[1], O_RDONLY);
    if (fd_in == -1)
        error_exit("open file1");

    // Open output file
    fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out == -1)
    {
        close(fd_in);
        error_exit("open file2");
    }

    // Create the pipe
    if (pipe(pipe_fd) == -1)
    {
        close(fd_in);
        close(fd_out);
        error_exit("pipe");
    }

    // Fork first child process for cmd1
    child1 = fork();
    if (child1 == -1)
    {
        close(fd_in);
        close(fd_out);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        error_exit("fork for cmd1");
    }
    if (child1 == 0)
    {
        // Child process for cmd1
        dup2(fd_in, STDIN_FILENO);      // Redirect input to file1
        dup2(pipe_fd[1], STDOUT_FILENO); // Redirect output to pipe write end
        close(fd_in);
        close(fd_out);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        execute_command(argv[2], envp); // Execute cmd1
    }

    // Fork second child process for cmd2
    child2 = fork();
    if (child2 == -1)
    {
        close(fd_in);
        close(fd_out);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        error_exit("fork for cmd2");
    }
    if (child2 == 0)
    {
        // Child process for cmd2
        dup2(pipe_fd[0], STDIN_FILENO);  // Redirect input to pipe read end
        dup2(fd_out, STDOUT_FILENO);    // Redirect output to file2
        close(fd_in);
        close(fd_out);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        execute_command(argv[3], envp); // Execute cmd2
    }

    // Parent process
    close(fd_in);
    close(fd_out);
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Wait for child processes
    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);

    return EXIT_SUCCESS;
}
