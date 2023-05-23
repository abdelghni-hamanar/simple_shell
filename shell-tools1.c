#include "shell.h"
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
		if ((_interactive(info) ||
					_getenv(info, "PATH=") ||
					info->argv[0][0] == '/') &&
				_is_cmd(info, info->argv[0]))
			_fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			_print_error(info, "not found\n");
		}
	}
}

