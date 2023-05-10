#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <linux/limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **environ;

/**
 * struct data - struct contains all relevant data
 * @av: argument
 * @input: command line entred by user
 * @args: token of command line
 * @status: last status of shell
 * @counter: lines counter
 * @_environ: env variable
 * @pid: child process
 */

typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sep_list_s - contains linked list signal
 * @separator: contains ; | &
 * @next: next node
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - linked list signal
 * @line: conatins command line
 * @next: next node
 */

typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct var_list_s - linked list signal
 * @len_var: len of variable
 * @val: valueof variable
 * @len_val: len of value
 * @next: next node
 */
typedef struct var_list_s
{
	int len_var;
	char *val;
	int len_val;
	struct var_list_s *next;
} r_var;

/**
 * struct builtin_s - struct for builtin
 * @name: name for command builtin i.e cd exit env etc
 * @f: data type pointer function
 */

typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;


#endif
