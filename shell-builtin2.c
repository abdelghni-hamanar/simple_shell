#include "shell.h"
/* Created By Abdelghni Hamanar and Emohammed*/
/**
 *_myhelp - display help
 *@info: struct for potential arguments
 *Return: 0 (Success)
 */
int _myhelp(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_puts("help call work, function net yet implemented \n");
	if (0)
		_puts(*arg_arr);
	return (0);
}
