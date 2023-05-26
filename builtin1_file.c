#include "main.h"
/**
* _myhistory_func - displays the history list, one command by line, preceded
*              with line numbers, starting at 0.
* @info_struct: Structure containing potential arguments.
*  Return: Always 0
*/
int _myhistory_func(info_t *info_struct)
{
	print_list_func(info_struct->history_var);
	return (0);
}
/**
* unset_alias_func - sets alias to string
* @info_struct: parameter struct
* @str_var: the string alias
* Return: Always 0 on success, 1 on error
*/
int unset_alias_func(info_t *info_struct, char *str_var)
{
	char *p_var, c_var;
	int ret_var;

	p_var = _strchr_func(str_var, '=');
	if (!p_var)
		return (1);
	c_var = *p_var;
	*p_var = 0;
	ret_var = delete_node_at_index_func(&(info_struct->alias_var),
		get_node_index_func(info_struct->alias_var,
			node_starts_with_func(info_struct->alias_var, str_var, -1)));
	*p_var = c_var;
	return (ret_var);
}
/**
* set_alias_func - sets alias to string
* @info_struct: parameter struct
* @str_var: the string alias
* Return: Always 0 on success, 1 on error
*/
int set_alias_func(info_t *info_struct, char *str_var)
{
	char *p_var;

	p_var = _strchr_func(str_var, '=');
	if (!p_var)
		return (1);
	if (!*++p_var)
		return (unset_alias_func(info_struct, str_var));
	unset_alias_func(info_struct, str_var);
	return (add_node_end_func(&(info_struct->alias_var), str_var, 0) == NULL);
}
/**
* print_alias_func - prints an alias string
* @node_struct: the alias node
* Return: Always 0 on success, 1 on error
*/
int print_alias_func(list_t *node_struct)
{
	char *p_var = NULL, *a_var = NULL;

	if (node_struct)
	{
		p_var = _strchr_func(node_struct->str_var, '=');
		for (a_var = node_struct->str_var; a_var <= p_var; a_var++)
			_putchar_func(*a_var);
		_putchar_func('\'');
		_puts_func(p_var + 1);
		_puts_func("'\n");
		return (0);
	}
	return (1);
}
/**
* _myalias_func - mimics the alias builtin (man alias)
* @info_struct: Structure containing potential arguments.
* Return: Always 0
*/
int _myalias_func(info_t *info_struct)
{
	int i_var = 0;
	char *p_var = NULL;
	list_t *node_struct = NULL;

	if (info_struct->argc == 1)
	{
		node_struct = info_struct->alias_var;
		while (node_struct)
		{
			print_alias_func(node_struct);
			node_struct = node_struct->next_var;
		}
		return (0);
	}
	for (i_var = 1; info_struct->argv[i_var]; i_var++)
	{
		p_var = _strchr_func(info_struct->argv[i_var], '=');
		if (p_var)
			set_alias_func(info_struct, info_struct->argv[i_var]);
		else
			print_alias_func(node_starts_with_func(info_struct->alias_var,
						info_struct->argv[i_var], '='));
	}
	return (0);
}
