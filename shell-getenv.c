#include "shell.h"
/* Created By Abdelghni Hamanar and Emohammed*/
/**
* _get_environ - return arr copy of environ
* @info: struct of params
* Return: 0 (Success)
*/

char **_get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = _list_to_string(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
* _unsetenv - remove env variable
* @info: struct of params
* @var: string env property
* Return: changed value
*/

int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = _starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = _delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}


/**
* _setenv - set new env variable
* @info: struct of params
* @var: string env property
* @value: value
* Return: 0 (Success)
*/

int _setenv(info_t *info, char *var, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);

	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env;
	while (node)
	{
		p = _starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	_add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
