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


extern char **environ

#define BUFFER_SIZE 1024

ssize_t __getline(char **, size_t *, FILE *);

int set_environment_variable(char **, char *, char *);
int unset_environment_variable(char **, char *);

/* handle the cd and PWD*/
void cd_command(char **, char **);

/*implement some function to reduce size of main function*/
void setenv_command(char **, char **);
void unsetenv_command(char **, char **);
void execute_command(char *, char **);

#endif
