#include "shell.h"
/* Created By Abdelghni Hamanar and Emohammed*/
/**
 * _hsh - main shell loop
 * @info: params & return info
 * @av: argument pointer from main
 * Return: 0 (Success), 1 (Error)
 */

int _hsh(info_t *info, char **av)
{
    ssize_t r = 0;
    int builtin_ret = 0;

    while (r != -1 && builtin_ret != -2)
    {
        _clear_info(info);
        if (_interactive(info))
            _puts("AH-EM$: ");
        _eputchar(BUF_FLUSH);
        r = _get_input(info);
        if (r != -1)
        {
            _set_info(info, av);
            builtin_ret = _find_builtin(info);
            if (builtin_ret == -1)
                _find_cmd(info);
        }
        else if (_interactive(info))
        {
            _putchar('\n');
        }
        _free_info(info, 0);
    }
    _write_history(info);
    _free_info(info, 1);
    if (!_interactive(info) && info->status)
        exit(info->status);
    if (builtin_ret == -2)
    {
        if (info->err_num == -1)
            exit(info->status);
        exit(info->err_num);
    }
    return (builtin_ret);
}
/* Created By Abdelghni Hamanar and Emohammed*/
/**
 * _find_builtin - find builtin command
 * @info: params & return info
 * Return: -1 if not found, 0 if execute success
 * 1 if found and execute not success
 * -2 if exit
 */

int _find_builtin(info_t *info)
{
    int i, built_in_ret = -1;
    builtin_table builtintbl[] = {
        {"exit", _myexit},
        {"env", _myenv},
        {"help", _myhelp},
        {"history", _myhistory},
        {"setenv", _mysetenv},
        {"unsetenv", _myunsetenv},
        {"cd", _mycd},
        {"alias", _myalias},
        {NULL, NULL}};

    for (i = 0; builtintbl[i].type; i++)
    {
        if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
        {
            info->line_count++;
            built_in_ret = builtintbl[i].func(info);
            break;
        }
    }
    return (built_in_ret);
}
/* Created By Abdelghni Hamanar and Emohammed*/
/**
 * _find_cmd - find the command path
 * @info: params & return info
 * Return: void
 */

void _find_cmd(info_t *info)
{
    char *path = NULL;
    int i, k;

    info->path = info->argv[0];
    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }
    for (i = 0, k = 0; info->arg[i]; i++)
    {
        if (!_is_delim(info->arg[i], " \t\n"))
            k++;
    }

    if (!k)
        return;

    path = _find_path(info, _getenv(info, "PATH="), info->argv[0]);
    if (path)
    {
        info->path = path;
        _fork_cmd(info);
    }
    else
    {
        if ((_interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && _is_cmd(info, info->argv[0]))
            _fork_cmd(info);
        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            _print_error(info, "not found\n");
        }
    }
}
/* Created By Abdelghni Hamanar and Emohammed*/
/**
 * _fork_cmd - forks and execute process to run command
 * @info: params & return info
 * Return: void
 */

void _fork_cmd(info_t *info)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error:");
        return;
    }
    if (child_pid == 0)
    {
        if (execve(info->path, info->argv, _get_environ(info)) == -1)
        {
            _free_info(info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
    }
    else
    {
        wait(&(info->status));
        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126)
                _print_error(info, "Permission denied\n");
        }
    }
}