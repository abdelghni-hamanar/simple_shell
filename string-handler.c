#include "shell.h"

/**
 * _strlen - return len of string
 * @s: the string counted
 * Return: len of string
 */

int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s++)
	{
		i++;
	}
	return (i);
}

/** by emmd and abdlaghni*/
/**
 * _strcmp - compare two strings
 * @s1: 1st string
 * @s2: 2nd string
 * Return: 0 if (s1 = 2), 1 if (s1 > s2), -1 if (s1 < s2)
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);

		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * _starts_with - check if needle start with haystack
 * @haystack: string to search
 * @needle: substring to find
 * Return: addres of next character of haystack or NULL
 */

char *_starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
			return (NULL);
	}
	return ((char *)haystack);
}

/**
 * _strcat - concat twi string
 * @dest: destination buffer
 * @src: source buffer
 * Return: pointer to desti buffer
 */

char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;

	*dest = *src;
	return (ret);
}
