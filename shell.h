#ifndef SHELL_H
#define SHELL_H

/* ALL LIBRARYS WE USE */
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

/* MACROS FOR READ AND WRITE BUFFERS */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* MACROS FOR CHAINING */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* MACROS FOR NUMBERS CONVERTION */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* MACROS FOR GETLINE */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* MACROS FOR HISTORY */

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

/* MACROS FOR GENERAL INFO */
#define INFO_INIT
{
	NULL, NULL, NULL, 0, 0, 0, 0, NULL,
		NULL, NULL, NULL, NULL,
		0, 0, NULL, 0, 0, 0
}

/* GL VAR */
extern char **environ;

/**
 * struct liststr - linked list
 * @num: field number
 * @str: string
 * @next: pointer to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - struct contains arguments to pass to the funct
 * @arg: string generate from getline
 * @argv: array of string generate from arg
 * @path: string path for the current command
 * @argc: argument count
 * @line_count: error count
 * @err_num: error code for exit
 * @linecount_flag: count line of inputs
 * @fname: file name
 * @env: linked list copy of env
 * @history: history node
 * @alias: alias node
 * @environ: pointer to environ
 * @env_changed: if env was changed
 * @status: return status of the list exec command
 * @cmd_buf: adress pointer to command buffer
 * @cmd_buf_type: ||, &&, ;
 * @readfd: fd from which read line input
 * @histcount: the history line number count
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

/**
 * struct builtin - struct for builtin
 * @type: pointer to string builtin
 * @func: pointer to func list_t
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* shell-tools.c - contains main function need it */
/* for our shell project */
int _hsh(info_t *, char **);
int _find_builtin(info_t *);
void _find_cmd(info_t *);
void _fork_cmd(info_t *);

/* shell-parser.c - contains all command parser */
int _is_cmd(info_t(info_t *, char *);
char *_dup_chars(char *, int, int);
char *_find_path(info_t *, char *, char *);

/* error-handler.c - handling errors */
void _eputs(char *);
int _eputchar(char);
int _putfd(char, int);
int _putsfd(char *, int);

/*string-handler.c - contains some string.h functions */
int _strlen(char *);
int _strcmp(char *, char *);
char *_starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string-handler1.c - continue... →→ */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* string-handler2.c - continue... →→→ */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* shell-tokenizer.c - contains function */
/* tokenize the command */
char **_strtow(char *, char *);
char **_strtow2(char *, char);

/* memory-handler.c - contains function handling memory */
char *_memset(char *, char, unsigned int);
void _ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int _bfree(void **);

/* shell-atoi.c - testing and converting into int */
int _interactive(info_t *);
int _is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* error-handler1.c - continue... →→ */
int _erratoi(char *);
void _print_error(info_t *, char *);
int _print_d(int, int);
char *_convert_number(long int, int, int);
void _remove_comment(char *);

/* shell-builtin.c - contains function handling builtin */
/* like cd →→  exit →→  help */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* shell-builtin1.c - continue →→ */
/* this time for history and alias */
int _myhistory(info_t *);
int _unset_alias(info_t *, char *);
int _set_alias(info_t *, char *);
int _print_alias(info_t *);
int _myalias(info_t *);

/* shell-getline.c - implement getline function */

ssize_t _get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void _sigintHandler(int);

/* shell-getinfo.c - handling info from shell */
void _clear_info(info_t *);
void _set_info(info_t *, char **);
void _free_info(info_t *, int);

/* shell-environ.c - handling env with set and unset */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int _populate_env_list(info_t *);

/* shell-getenv.c -implementing function */
/* from shell-environ.c */
char **_get_environ(info_t *);
int _setenv(info_t *, char *, char *);
int _unsetenv(info_t *, char *);

/* shell-history.c - handling history command */
char *_get_history_file(info_t *);
int _write_history(info_t *);
int read_history(info_t *);
int _build_history_list(info_t *, char *, int);
int _renumber_history(info_t *);

/* shell-linked.c - handling nodes */
list_t *_add_node(list_t **, const char *, int);
list_t *_add_node_end(list_t **, const char *, int);
size_t _print_list_str(const list_t *);
int _delete_node_at_index(list_t **, unsigned int);
void _free_list(list_t **);

/* shell-linked1.c - continue... →→ */
size_t _list_len(const list_t *);
char **_list_to_string(list_t *);
size_t _print_list(const list_t *);
list_t *_node_starts_with(list_t *, char *, char);
ssize_t _get_node_index(list_t *, list_t *);

/* shell-variables.c - handling shell variables */
int _is_chain(info_t *, char *, size_t *);
void _check_chain(info_t *, char *, size_t *, size_t, size_t);
int _replace_alias(info_t *);
int _replace_vars(info_t *);
int _replace_string(char **, char *);

#endif
