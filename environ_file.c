#include "main.h"
/**
* _myenv_func - prints the current environment
* @info_struct: Structure containing potential arguments.
* Return: Always 0
*/
int _myenv_func(info_t *info_struct)
{
	print_list_str_func(info_struct->env_var);
	return (0);
}
/**
* _getenv_func - gets the value of an environ variable
* @info_struct: Structure containing potential arguments.
* @name_var: env var name
* Return: the value
*/
char *_getenv_func(info_t *info_struct, const char *name_var)
{
	list_t *node_struct = info_struct->env_var;
	char *p_var;

	while (node_struct)
	{
		p_var = starts_with_func(node_struct->str_var, name_var);
		if (p_var && *p_var)
			return (p_var);
		node_struct = node_struct->next_var;
	}
	return (NULL);
}
/**
* _mysetenv_func - Initialize or modify environment variable
* @info_struct: Structure containing potential arguments
* Return: Always 0
*/
int _mysetenv_func(info_t *info_struct)
{
	if (info_struct->argc != 3)
	{
		_eputs_func("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv_func(info_struct, info_struct->argv[1], info_struct->argv[2]))
		return (0);
	return (1);
}
/**
* _myunsetenv_func - Remove an environment variable
* @info_struct: Structure containing potential arguments.
* Return: Always 0
*/
int _myunsetenv_func(info_t *info_struct)
{
	int i_var;

	if (info_struct->argc == 1)
	{
		_eputs_func("Too few arguements.\n");
		return (1);
	}
	for (i_var = 1; i_var <= info_struct->argc; i_var++)
		_unsetenv_func(info_struct, info_struct->argv[i_var]);
	return (0);
}
/**
* populate_env_list_func - populates env linked list
* @info_struct: Structure containing potential arguments.
* Return: Always 0
*/
int populate_env_list_func(info_t *info_struct)
{
	list_t *node_struct = NULL;
	size_t i_var;

	for (i_var = 0; environ[i_var]; i_var++)
		add_node_end_func(&node_struct, environ[i_var], 0);
	info_struct->env_var = node_struct;
	return (0);
}





