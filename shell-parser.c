#include "shell.h"

/**
 * _is_cmd - determins if file an execut command
 * @info: info struct
 * @path: path of the file
 * Return: 1 (Success), 0 (Fail)
 */
int _is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;

	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _dup_chars - duplicats chars
 * @pathstr: path string
 * @start: starting index
 * @stop: stoppping index
 * Return: pointer to the new buffer
 */

char *_dup_chars(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buffer[k++] = pathstr[i];

	buffer[k] = 0;
	return (buffer);
}

/**
 * _find_path - finds command path string
 * @info: info struct
 * @pathstr: path string
 * @cmd: command to find
 * Return: full path if found or null
 */

char *_find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && _starts_with(cmd, "./"))
	{
		if (_is_cmd(info, cmd))
			return (cmd);
	}

	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = _dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (_is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
