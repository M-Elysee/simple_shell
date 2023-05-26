#include "main.h"
/**
* get_environ_func - returns the string array copy of our environ
* @info_struct: Structure containing potential arguments.
* Return: Always 0
*/
char **get_environ_func(info_t *info_struct)
{
	if (!info_struct->environ || info_struct->env_changed_var)
	{
		info_struct->environ = list_to_strings_func(info_struct->env_var);
		info_struct->env_changed_var = 0;
	}

	return (info_struct->environ);
}
/**
* _unsetenv_func - Remove an environment variable
* @info_struct: Structure containing potential arguments.
* @var_var: the string env var property
* Return: 1 on delete, 0 otherwise
*/
int _unsetenv_func(info_t *info_struct, char *var_var)
{
	list_t *node_struct = info_struct->env_var;
	size_t i_var = 0;
	char *p_var;

	if (!node_struct || !var_var)
		return (0);

	while (node_struct)
	{
		p_var = starts_with_func(node_struct->str_var, var_var);
		if (p_var && *p_var == '=')
		{
			info_struct->env_changed_var =
				delete_node_at_index_func(&(info_struct->env_var), i_var);
			i_var = 0;
			node_struct = info_struct->env_var;
			continue;
		}
		node_struct = node_struct->next_var;
		i_var++;
	}
	return (info_struct->env_changed_var);
}
/**
* _setenv_func - Initialize a new environment variable,
*             or modify an existing one
* @info_struct: Structure containing potential arguments.
* @var_var: the string env var property
* @value_var: the string env var value
* Return: Always 0
*/
int _setenv_func(info_t *info_struct, char *var_var, char *value_var)
{
	char *buf_var = NULL;
	list_t *node_struct;
	char *p_var;

	if (!var_var || !value_var)
		return (0);

	buf_var = malloc(_strlen_func(var_var) + _strlen_func(value_var) + 2);
	if (!buf_var)
		return (1);
	_strcpy_func(buf_var, var_var);
	_strcat_func(buf_var, "=");
	_strcat_func(buf_var, value_var);
	node_struct = info_struct->env_var;
	while (node_struct)
	{
		p_var = starts_with_func(node_struct->str_var, var_var);
		if (p_var && *p_var == '=')
		{
			free(node_struct->str_var);
			node_struct->str_var = buf_var;
			info_struct->env_changed_var = 1;
			return (0);
		}
		node_struct = node_struct->next_var;
	}
	add_node_end_func(&(info_struct->env_var), buf_var, 0);
	free(buf_var);
	info_struct->env_changed_var = 1;
	return (0);
}
