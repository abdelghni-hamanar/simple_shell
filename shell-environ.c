#include "shell.h"
/**
* _myenv - print env
* @info: struct of params
* Return: 0 (Success)
*/

int _myenv(info_t *info)
{
	_print_list_str(info->env);
	return (0);
}

/**
* _getenv - get env value
* @info: struct of params
* @name: env name
* Return: env value
*/

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = _starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
* _mysetenv - create env variable
* @info: struct of params
* Return: 0 (Success)
*/

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}

/**
* _myunsetenv - create env variable
* @info: struct of params
* Return: 0 (Success)
*/

int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("To few arguments.\n");
		return (1);
	}
	for (i = 0; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
* _populate_env_list - env linked list
* @info: struct of params
* Return: 0 (Success)
*/

int _populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		_add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
