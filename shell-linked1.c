#include "shell.h"

/**
 * _list_len - len of linked
 * @h: pointer 1st node
 * Return: size of list
 */
size_t _list_len(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        h = h->next;
        i++;
    }
    return (i);
}

/** by emmd and abdlaghni*/
/**
 * _list_to_string - return arr string list str
 * @head: pointer 1st node
 * Return: arr of string
 */

char **_list_to_string(list_t *head)
{
    list_t *node = head;
    size_t i = _list_len(head), j;
    char **strs, *str;

    if (!head || !i)
        return (NULL);
    strs = malloc(sizeof(char *) * (i + 1));
    if (!strs)
        return (NULL);
    for (i = 0; node; node = node->next, i++)
    {
        str = malloc(_strlen(node->str) + 1);
        if (!str)
        {
            for (j = 0; j < i; j++)
                free(strs[j]);
            free(strs);
            return (NULL);
        }

        str = _strcpy(str, node->str);
        strs[i] = str;
    }
    strs[i] = NULL;
    return (strs);
}

/**
 * _print_list - print elem of linked
 * @h: point 1st node
 * Return: size of node
 */

size_t _print_list(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        _puts(_convert_number(h->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
        i++;
    }
    return (i);
}

/**
 * _node_starts_with - return node start with prefix
 * @node: pointer 1st node
 * @prefix: string to match
 * @c: next char after prefix to much
 * Return: match node or null
 */

list_t *_node_starts_with(list_t *node, char *prefix, char c)
{
    char *p = NULL;

    while (node)
    {
        p = _starts_with(node->str, prefix);
        if (p && ((c == -1) || (*p == c)))
            return (node);
        node = node->next;
    }
    return (NULL);
}

/**
 * _get_node_index - get index of node
 * @head: point 1st head
 * @node: point to node
 * Return: index of node
 */

ssize_t _get_node_index(list_t *head, list_t *node)
{
    size_t i = 0;

    while (head)
    {
        if (head == node)
            return (i);
        head = head->next;
        i++;
    }
    return (-1);
}