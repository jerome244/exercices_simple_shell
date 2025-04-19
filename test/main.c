#include "shell.h"

/**
 * main - main function
 *
 * Return: always 0
 */

int main(void)
{
	char *prompt, **array, *temp, *command, **path, *env_var;
	int status, i = 0;
	pid_t pid;

	path = pathfinder();
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		prompt = _getline();
		if (!prompt)
		{
			break;
		}
		array = splitter(prompt, " \n\t");
		free(prompt);
		if (!*array)
		{
			free(array);
			continue;
		}
		if (strcmp(array[0], "exit") == 0)
		{
			if (array[1] != NULL)
			{
				_exit(2);
			}
			else
			{
				_exit(0);
			}
		}
		else
			if (strcmp(array[0], "env") == 0)
			{
				if (array[1] && strcmp(array[1], "-i") == 0)
				{
					env_var = array[2];
					_env(env_var);
				}
				else
					_env(NULL);
			}
			else
				pid = fork();
		if (pid == 0)
		{
			command = strdup(array[0]);
			execve(array[0], array, environ);
			while (path[i])
			{
				execve(array[0], array, environ);
				temp = malloc(strlen(path[i]) + strlen(command) + 1);
				strcpy(temp, path[i]);
				strcat(temp, command);
				free(array[0]);
				array[0] = strdup(temp);
				free(temp);
				i++;
			}
			printf("No such file or directory\n");
			exit(EXIT_FAILURE);
		}
		else
			wait(&status);
		for (i = 0; *(array + i); i++)
			free(*(array + i));
		free(array);
	}
	for (i = 0; *(path + i); i++)
		free(*(path + i));
	free(path);
	free(prompt);
	return (0);
}
