#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>
#include <signal.h>

int _putchar(char c);
void _printstr(char *str);
int _strlen(char *s);
char *_copystr(char *str);
char *concat_strings(char *str1, char *str2, char *str3);

char **split(char *s, const char *d);
void run(char **args);
void *_resize(void *old, unsigned int os, unsigned int ns);


extern char **environ;

/**
 * struct list_path - Linked list containing PATH directories
 * @dir: directory in path
 * @next: pointer to next node
 */
typedef struct list_path
{
	char *dir;
	struct list_path *next;
} list_path;


char *_getvar(const char *var);
list_path *add_node(list_path **start, char *s);
list_path *create_path(char *p);
char *_findpath(char *file, list_path *start);

/**
 * struct mybuild - pointer to function with corresponding buildin command
 * @name: buildin command
 * @func: execute the buildin command
 */
typedef struct mybuild
{
	char *name;
	void (*func)(char **);
} mybuild;

void(*checkBuiltInCmd(char **cmdArgs))(char **);
int _atoi(char *s);
void exitShell(char **cmdArv);
void printEnv(char **cmdArv);
void setEnvVar(char **cmdArv);
void unsetEnvVar(char **cmdArv);

void free_arr(char **arr);
void free_nodes(list_path *start);


#endif
