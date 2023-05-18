#include "shell.h"

/**
* _input_buf - buffer chained
* @info: struct of params
* @buffer: adress of buffer
* @len: aress of len
* Return: readed byte
*/

ssize_t _input_buf(info_t *info, char **buffer, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, _sigintHandler);
#if USE_GETLINE
		r = getline(buffer, &len_p, stdin);
#else
		r = _getline(info, buffer, &len_p);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			_remove_comment(*buffer);
			_build_history_list(info, *buffer, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buffer;
			}
		}
	}
	return (r);
}

/**
* _get_input - gets line - the new line
* @info: struct of params
* Return: readed byte
*/

ssize_t _get_input(info_t *info)
{
	static char *buffer;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buffer_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = _input_buf(info, &buffer, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buffer + i;
		_check_chain(info, buffer, &j, i, len);
		while (j < len)
		{
			if (_is_chain(info, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buffer_p = p;
		return (_strlen(p));
	}
	*buffer_p = buffer;
	return (r);
}

/**
* _read_buf - read a buffer
* @info: struct of params
* @buf: buffer
* @i: size
* Return: r
*/

ssize_t _read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
* _getline - gets next line
* @info: struct of params
* @ptr: adress of buffer
* @lenght: size
* Return: s
*/

int _getline(info_t *info, char **ptr, size_t *lenght)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL;
	char *new_p = NULL, *c;

	p = *ptr;
	if (p && lenght)
		s = *lenght;
	if (i == len)
		i = len = 0;

	r = _read_buf(info, buffer, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strchr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (s)
		_strncat(new_p, buffer + i, k - i);
	else
		_strncpy(new_p, buffer + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;
	if (lenght)
		*lenght = s;
	*ptr = p;
	return (s);
}

/**
* _sigintHandler - blocks ctr-c
* @sig: signal number
* Return: void
*/

void _sigintHandler(__attribute__((unused)) int sig)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
