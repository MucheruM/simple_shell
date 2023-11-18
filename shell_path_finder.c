#include "shell.h"

/**
 * _getvar - Retrieve the value of the specified global variable
 * @var: The identifier of the global variable
 * Return: String rep the value of the global variable
 */
char *_getvar(const char *var)
{
	int a, b;
	char *val;

	if (!var)
		return (NULL);
	for (a = 0; environ[a]; a++)
	{
		b = 0;
		if (var[b] == environ[a][b])
		{
			while (var[b])
			{
				if (var[b] != environ[a][b])
					break;
				b++;
			}
			if (var[b] == '\0')
			{
				val = (environ[a] + b + 1);
				return (val);
			}
		}
	}
	return (0);
}

/**
 * add_node - This function adds a new node at the end of a list_t list
 * @start: This is a pointer to pointer to the linked list
 * @s: The string in previous first node
 * Return: The address of the new node
 */
list_path *add_node(list_path **start, char *s)
{
	list_path *temp;
	list_path *new_node;

	new_node = malloc(sizeof(list_path));

	if (!new_node || !s)
	{
		return (NULL);
	}

	new_node->dir = s;

	new_node->next = '\0';
	if (!*start)
	{
		*start = new_node;
	}
	else
	{
		temp = *start;

		while (temp->next)
		{
			temp = temp->next;
		}

		temp->next = new_node;
	}

	return (*start);
}

/**
 * create_path - The func creates a linked list for path directories
 * @p: A string rep of path value
 * Return: A pointer to the head of the created linked list
 */
list_path *create_path(char *p)
{
	list_path *start = '\0';
	char *tok;
	char *cp = _copystr(p);

	tok = strtok(cp, ":");
	while (tok)
	{
		start = add_node(&start, tok);
		tok = strtok(NULL, ":");
	}

	return (start);
}

/**
 * _findpath - The function finds the pathname of a filename
 * @file: The name of file or command
 * @start: A pointer to the head of linked list of path directories
 * Return: A string rep a full pathname of file
 */
char *_findpath(char *file, list_path *start)
{
	struct stat st;
	char *str;

	list_path *temp = start;

	while (temp)
	{
		str = concat_strings(temp->dir, "/", file);
		if (stat(str, &st) == 0)
		{
			return (str);
		}
		free(str);
		temp = temp->next;
	}

	return (NULL);
}

/**
 * free_nodes - The function frees a linked list
 * @start: This is a pointer to the head of the linked list
 */
void free_nodes(list_path *start)
{
	list_path *store;

	while (start)
	{
		store = start->next;
		free(start->dir);
		free(start);
		start = store;
	}
}
