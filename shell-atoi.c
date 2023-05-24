#include "shell.h"
/* Created By Abdelghni Hamanar and Emohammed*/
/**
 * _interactive - check if shell is interactive
 * @info: pointer to the struct contains info
 * Return: 1 (interactive), 0 if not
 */

int _interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * _is_delim - check if is delim
 * @c: char to check
 * @delim: delim string
 * Return: 1 (true), 0 if not
 */

int _is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);

	return (0);
}

/**
 * _isalpha - check if is alpha
 * @c: char to check
 * Return: 1 (true), 0 if not
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - convert string to int
 * @s: string to convert
 * Return: 0 if no number found, convert if any
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int res = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -res;
	else
		output = res;

	return (output);
}
