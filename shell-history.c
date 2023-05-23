#include "shell.h"

/** by emmd and abdlaghni*/
/**
 * _get_history_file - get history
 * @info: struct
 * Return: history file
 */

char *_get_history_file(info_t *info)
{
	char *buffer, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, dir);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}
/** by emmd and abdlaghni*/
/**
 * _write_history - create file append exiting file
 * @info: struct
 * Return: 1 (Success), -1 (Fail)
 */

int _write_history(info_t *info)
{
	ssize_t fd;
	char *filename = _get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/** by emmd and abdlaghni*/
/**
 * read_history - read hist file
 * @info: struct
 * Return: sit when (Success), 0 (Fail)
 */

int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = _get_history_file(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(fd, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(fd);

	for (i = 0; i < fsize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			_build_history_list(info, buffer + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		_build_history_list(info, buffer + last, linecount++);
	free(buffer);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		_delete_node_at_index(&(info->history), 0);
	_renumber_history(info);
	return (info->histcount);
}

/** by emmd and abdlaghni*/
/**
 * _build_history_list - add entrys to history linked list
 * @info: struct
 * @buf: buffer
 * @linecount: histcount
 * Return: 0 (Success)
 */

int _build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	_add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * _renumber_history - renumber history
 * @info: struct
 * Return: new history
 */

int _renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
