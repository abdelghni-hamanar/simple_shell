#include "shell.h"
/* Created By Abdelghni Hamanar and Emohammed*/
/**
 * _erratoi - convert string to int
 * @s: string to be converted
 * Return: 0 if no num in the string, -1 (Error), num if true
 */

int _erratoi(char *s)
{
	int i = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			res *= 10;
			res += (s[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * _print_error - print error msg
 * @info: struct contains params & return info
 * @estr: string contains specific error
 * Return: 0 if no num in the string, -1 (Error), num if true
 */

void _print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	_print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_puts(": ");
	_eputs(estr);
}

/**
 * _print_d - print decimal number base 10
 * @input: input
 * @fd: fd to write to
 * Return: num if char printed
 */

int _print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * _convert_number - clone of itoi
 * @num: number
 * @base: base
 * @flags: argument
 * Return: string
 */
char *_convert_number(long int num, int base, int flags)
{
	static char *arr;
	static char buffer[50];
	char sign = 0, *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = arr[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * _remove_comment - replace 1st instance of # with \0
 * @buf: adress of string to modify
 * Return: void
 */

void _remove_comment(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}
