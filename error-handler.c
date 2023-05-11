#include "shell.h"
/* BY ABDELGHNI HAMANAR AND EMOHAMEDD */
/**
 * _eputs - prints input string
 * @str: string printed
 * Return: void
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}
/**
 * _eputchar - write char c to stderr
 * @c: char to print
 * Return: 1 (Success), -1 (Fail)
 */
int _eputchar(char c)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buffer[i++] = c;

	return (1);
}

/**
 * _putfd - write char c to a given fd
 * @c: char to print
 * @fd: fd to write
 * Return: 1 (Success), -1 (Fail)
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buffer[i++] = c;

	return (1);
}

/**
 * _putsfd - print input string
 * @str: string to print
 * @fd: fd to write
 * Return: number of char
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str)
		i += _putfd(*str++, fd);

	return (i);
}
