#include "shell.h"

/**
* _myhistory - display history
* @info: struct contains all arguments
* Return: 0 (Success)
*/

int _myhistory(info_t *info)
{
	_print_list(info->history);
	return (0);
}

/**
* _unset_alias - unset alias
* @info: struct contains all arguments
* @str: alias string
* Return: 0 (Success), 1 (Fail)
*/

int _unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);

	c = *p;
	*p = 0;
	ret = _delete_node_at_index(&(info->alias),
			_get_node_index(info->alias,
				_node_starts_with(info->alias, str, -1)));
	*p = c;

	return (ret);
}
/**
* _set_alias - set alias
* @info: struct contains all arguments
* @str: alias string
* Return: 0 (Success), 1 (Fail)
*/

int _set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (_unset_alias(info, str));

	_unset_alias(info, str);
	return (_add_node_end(&(info->alias), str, 0) == NULL);
}
/**
* _print_alias - print alias
* @node: alias linked list
* Return: 0 (Success), 1 (Fail)
*/
int _print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);

		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
* _myalias - alias built
* @info: struct contains all arguments
* Return: 0 (Success)
*/

int _myalias(info_t *info)
{
	int  i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			_print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 0; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			_set_alias(info, info->argv[i]);
		else
			_print_alias(_node_starts_with(info->alias, info->argv[i], '='));
	}
	return (0);
}
