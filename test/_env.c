#include "shell.h"

/*
 * env_shell - function to implement env command
 * @env_var: pointer to an array of env variables
 */
void _env(char *env_var)
{
	char *env_vars[2], **env;

	if (env_var)
	{
		env_vars[0] = env_var;
		env_vars[1] = NULL;
		execve("/usr/bin/env", env_vars, NULL);
	}
	else
	{
		for (env = environ; *env != NULL; env++)
		{
			printf("%s\n", *env);
		}
	}
}
