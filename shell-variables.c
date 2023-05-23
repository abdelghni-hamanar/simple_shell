#include "shell.h"

/** by emmd and abdlaghni*/
/**
 * _is_chain - test if curr char in buffer
 * @info: struct
 * @buf: the char buffer
 * @p: adreese the current position
 * Return: 1 if chai delim, 0 if not
 */

int _is_chain(info_t *info, char *buf, size_t *p)
{
	size_t i = *p;

	if (buf[i] == '|' && buf[i + 1] == '|')
	{
		buf[i] = 0;
		i++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[i] == '&' && buf[i + 1] == '&')
	{
		buf[i] = 0;
		i++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[i] == ';')
	{
		buf[i] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = i;
	return (1);
}

/**
 * _check_chain - check and continue chaining
 * @info: struct
 * @buf: char buffer
 * @p: adress current pos
 * @i: starting pos in buf
 * @len: len of buffer
 * Return: void
 */

void _check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * _replace_alias - replace aliases in tokenize string
 * @info: params
 * Return: 1 if (replaced), 0 if not
 */

int _replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = _node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (0);
}

/**
 * _replace_vars - replace var in tokenized string
 * @info: params struct
 * Return: 1 (Success), 0 (Fail)
 */

int _replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			_replace_string(&(info->argv[i]),
					_strdup(_convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			_replace_string(&(info->argv[i]),
					_strdup(_convert_number(getpid(), 10, 0)));
			continue;
		}
		node = _node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			_replace_string(&(info->argv[i]), _strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		_replace_string(&info->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * _replace_string - replace string
 * @old: old one
 * @new: new one
 * Return: 1 if replaced, 0 if not
 */

int _replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
