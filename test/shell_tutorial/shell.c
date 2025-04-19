#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(void)
{
    char *buf = NULL;
    size_t buf_size = 0;
    ssize_t nread;
    pid_t pid;
    int status;
    char *argv[2];

    while (1)
    {
        write(STDOUT_FILENO, "#cisfun$ ", 9);

        nread = getline(&buf, &buf_size, stdin);
        if (nread == -1)
        {
            write(STDOUT_FILENO, "\n", 1);  /*For clean exit on Ctrl+D*/
            break;
        }

        // Remove trailing newline
        if (buf[nread - 1] == '\n')
            buf[nread - 1] = '\0';

        if (buf[0] == '\0')
            continue;

        pid = fork();
        if (pid < 0)
        {
            perror("fork");
            continue;
        }

        if (pid == 0)
        {
            argv[0] = buf;
            argv[1] = NULL;
            execve(buf, argv, NULL);
            perror("./shell");
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(&status);
        }
    }
    free(buf);
}
