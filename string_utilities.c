#include "shell.h"

/**
 * _copystr - A func that returns a pointer to a newly allocated space in mem
 * which contains a copy of the input string
 * @input: pointer to a string
 * Return: pointer to a string
 */
char *_copystr(char *input)
{
	int a, len;
	char *new_str;

	if (!input)
	{
		return (NULL);
	}
	for (len = 0; input[len] != '\0';)
	{
		len++;
	}
	new_str = malloc(sizeof(char) * len + 1);
	if (!new_str)
	{
		return (NULL);
	}
	for (a = 0; a < len; a++)
	{
		new_str[a] = input[a];
	}
	new_str[len] = input[len];
	return (new_str);
}

/**
 * concat_strings - A func that concantenates 3 strings in a new memory
 * @str1: The first string
 * @str2: The second string
 * @str3: The third string
 * Return: A pointer to the newly concatenated string
 */
char *concat_strings(char *str1, char *str2, char *str3)
{
	char *result_str;
	int len1, len2, len3, a, j;

	len1 = _strlen(str1);
	len2 = _strlen(str2);
	len3 = _strlen(str3);

	result_str = malloc(len1 + len2 + len3 + 1);
	if (!result_str)
		return (NULL);

	for (a = 0; str1[a]; a++)
		result_str[a] = str1[a];
	j = a;

	for (a = 0; str2[a]; a++)
		result_str[j + a] = str2[a];
	j = j + a;

	for (a = 0; str3[a]; a++)
		result_str[j + a] = str3[a];
	j = j + a;

	result_str[j] = '\0';

	return (result_str);
}

/**
 * _strlen - calculate the length of a string
 * @str: The string whose length is to be calculated
 * Return: The calculated length of the string
 */
int _strlen(char *str)
{
	int a = 0;

	while (*(str + a) != '\0')
	{
		a++;
	}
	return (a);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: 1 on Successfully writing
 * On error return -1, setting errno appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _printstr - Outputs a string to the stdout
 * @str: The string to be output
 */

void _printstr(char *str)
{
	int a = 0;

	while (str[a])
	{
		_putchar(str[a]);
		a++;
	}
}
