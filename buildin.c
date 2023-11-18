#include "shell.h"

/**
 * exitShell - Exits the shell with or without a status return of n
 * @args: Array of words of the entered line
 */
void exitShell(char **args)
{
	int index, exitStatus;

	if (args[1])
	{
		exitStatus = _atoi(args[1]);
		if (exitStatus <= -1)
			exitStatus = 2;
		free_arr(args);
		exit(exitStatus);
	}
	for (index = 0; args[index]; index++)
		free(args[index]);
	free(args);
	exit(0);
}

/**
 * _atoi - Converts a string into an integer
 *@str: Pointer to a string
 *Return: The integer representation of the string
 */
int _atoi(char *str)
{
	int index, integerVal, sign = 1;

	index = 0;
	integerVal = 0;
	while (!((str[index] >= '0') && (str[index] <= '9')) && (str[index] != '\0'))
	{
		if (str[index] == '-')
		{
			sign = sign * (-1);
		}
		index++;
	}
	while ((str[index] >= '0') && (str[index] <= '9'))
	{
		integerVal = (integerVal * 10) + (sign * (str[index] - '0'));
		index++;
	}
	return (integerVal);
}

/**
 * printEnv - Prints the current environment
 * @args: Array of arguments
 */
void printEnv(char **args __attribute__ ((unused)))
{

	int index;

	for (index = 0; environ[index]; index++)
	{
		puts(environ[index]);
		puts("\n");
	}

}

/**
 * setEnvVar - Initializes a new env variable, or modifies an existing one
 * @args: Array of entered words
 */
void setEnvVar(char **args)
{
	int oi, ii, vi;

	if (!args[1] || !args[2])
	{
		perror(getenv("_"));
		return;
	}

	for (oi = 0; environ[oi]; oi++)
	{
		ii = 0;
		if (args[1][ii] == environ[oi][ii])
		{
			while (args[1][ii])
			{
				if (args[1][ii] != environ[oi][ii])
					break;

				ii++;
			}
			if (args[1][ii] == '\0')
			{
				vi = 0;
				while (args[2][vi])
				{
					environ[oi][ii + 1 + vi] = args[2][vi];
					vi++;
				}
				environ[oi][ii + 1 + vi] = '\0';
				return;
			}
		}
	}
	if (!environ[oi])
	{

		environ[oi] = concat_strings(args[1], "=", args[2]);
		environ[oi + 1] = '\0';

	}
}

/**
 * unsetEnvVar - Removes an environment variable
 * @args: Array of entered words
 */
void unsetEnvVar(char **args)
{
	int oi, ii;

	if (!args[1])
	{
		perror(_getvar("_"));
		return;
	}
	for (oi = 0; environ[oi]; oi++)
	{
		ii = 0;
		if (args[1][ii] == environ[oi][ii])
		{
			while (args[1][ii])
			{
				if (args[1][ii] != environ[oi][ii])
					break;

				ii++;
			}
			if (args[1][ii] == '\0')
			{
				free(environ[oi]);
				environ[oi] = environ[oi + 1];
				while (environ[oi])
				{
					environ[oi] = environ[oi + 1];
					oi++;
				}
				return;
			}
		}
	}
}
