#include "shell.h"

/**
* checkBuiltInCmd - Verifies if the command is a built-in command
* @cmdArgs: array of command arguments
* Return: Pointer to function that takes cmdArgs and returns void
*/
void(*checkBuiltInCmd(char **cmdArgs))(char **cmdArgs)
{
	int oi, ii;

	mybuild builtInFuncs[] = {
		{"exit", exitShell},
		{"env", printEnv},
		{"setenv", setEnvVar},
		{"unsetenv", unsetEnvVar},
		{NULL, NULL}
	};

	for (oi = 0; builtInFuncs[oi].name; oi++)
	{
		ii = 0;
		if (builtInFuncs[oi].name[ii] == cmdArgs[0][ii])
		{
			for (ii = 0; cmdArgs[0][ii]; ii++)
			{
				if (builtInFuncs[oi].name[ii] != cmdArgs[0][ii])
					break;
			}
			if (!cmdArgs[0][ii])
				return (builtInFuncs[oi].func);
		}
	}
	return (0);
}
