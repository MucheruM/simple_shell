#include "shell.h"

/**
 * signalHandler - Handles the SIGINT signal (Ctrl+C)
 * @signalNumber: The signal number
 */
void signalHandler(int signalNumber)
{
	if (signalNumber == SIGINT)
	{
		_printstr("\n#cisfun$ ");
	}
}

/**
* handleEOF - Handles the End of File condition
* @readLength: return value of getline function
* @buffer: input buffer
 */
void handleEOF(int readLength, char *buffer)
{
	(void)buffer;
	if (readLength == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			_printstr("\n");
			free(buffer);
		}
		exit(0);
	}
}
/**
  * checkIsatty - Checks if the input is from a terminal
  */

void checkIsatty(void)
{
	if (isatty(STDIN_FILENO))
		_printstr("#cisfun$ ");
}
/**
 * main - Entry point for the shell program
 * Return: 0 on success
 */

int main(void)
{
	ssize_t readLength = 0;
	char *buffer = NULL, *envValue, *path, **args;
	size_t buffSize = 0;
	list_path *head = '\0';
	void (*func)(char **);

	signal(SIGINT, signalHandler);
	while (readLength != EOF)
	{
		checkIsatty();
		readLength = getline(&buffer, &buffSize, stdin);
		handleEOF(readLength, buffer);
		args = split(buffer, " \n");
		if (!args || !args[0])
			run(args);
		else
		{
			envValue = _getvar("PATH");
			head = create_path(envValue);
			path = _findpath(args[0], head);
			func = checkBuiltInCmd(args);
			if (func)
			{
				free(buffer);
				func(args);
			}
			else if (!path)
				run(args);
			else if (path)
			{
				free(args[0]);
				args[0] = path;
				run(args);
			}
		}
	}
	free_nodes(head);
	free_arr(args);
	free(buffer);
	return (0);
}
