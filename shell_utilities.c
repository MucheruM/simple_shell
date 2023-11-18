#include "shell.h"

/**
 * split - Divides a string into an array of pointers to words
 * @s: the string to be divided
 * @d: the delimiter or separator
 * Return: array of pointers to words
 */
char **split(char *s, const char *d)
{
	int a, wc;
	char **arr;
	char *tok;
	char *cp;

	cp = malloc(_strlen(s) + 1);
	if (cp == NULL)
	{
		perror(_getvar("_"));
		return (NULL);
	}
	a = 0;
	while (s[a])
	{
		cp[a] = s[a];
		a++;
	}
	cp[a] = '\0';

	tok = strtok(cp, d);
	arr = malloc((sizeof(char *) * 2));
	arr[0] = strdup(tok);

	a = 1;
	wc = 3;
	while (tok)
	{
		tok = strtok(NULL, d);
		arr = _resize(arr, (sizeof(char *) * (wc - 1)), (sizeof(char *) * wc));
		arr[a] = strdup(tok);
		a++;
		wc++;
	}
	free(cp);
	return (arr);
}

/**
 * run - Carries out a command
 * @args: array of command arguments
 */
void run(char **args)
{
	int p, st;

	if (!args || !args[0])
		return;
	p = fork();
	if (p == -1)
	{
		perror(_getvar("_"));
	}
	if (p == 0)
	{
		execve(args[0], args, environ);
		perror(args[0]);
		exit(EXIT_FAILURE);
	}
	wait(&st);
}

/**
 * _resize - Reallocates the size of a memory block
 * @old: initial pointer
 * @os: initial size of the pointer
 * @ns: new size for our pointer
 * Return: Pointer with adjusted size
 */
void *_resize(void *old, unsigned int os, unsigned int ns)
{
	char *n;
	char *o;

	unsigned int j;

	if (old == NULL)
		return (malloc(ns));

	if (ns == os)
		return (old);

	if (ns == 0 && old != NULL)
	{
		free(old);
		return (NULL);
	}

	n = malloc(ns);
	o = old;
	if (n == NULL)
		return (NULL);

	if (ns > os)
	{
		for (j = 0; j < os; j++)
			n[j] = o[j];
		free(old);
		for (j = os; j < ns; j++)
			n[j] = '\0';
	}
	if (ns < os)
	{
		for (j = 0; j < ns; j++)
			n[j] = o[j];
		free(old);
	}
	return (n);
}

/**
 * free_arr - frees memory for the pointers array
 * @arr: array of pointers
 */
void free_arr(char **arr)
{
	int j;

	for (j = 0; arr[j]; j++)
		free(arr[j]);
	free(arr);
}
