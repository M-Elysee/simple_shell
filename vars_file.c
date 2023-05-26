#include "main.h"
/**
* is_chain_func - test if current char in buffer is a chain delimeter
* @info_struct: the parameter struct
* @buf_var: the char buffer
* @p_var: address of current position in buf
* Return: 1 if chain delimeter, 0 otherwise
*/
int is_chain_func(info_t *info_struct, char *buf_var, size_t *p_var)
{
	size_t j_var = *p_var;

	if (buf_var[j_var] == '|' && buf_var[j_var + 1] == '|')
	{
		buf_var[j_var] = 0;
		j_var++;
		info_struct->cmd_buf_type_var = CMD_OR;
	}
	else if (buf_var[j_var] == '&' && buf_var[j_var + 1] == '&')
	{
		buf_var[j_var] = 0;
		j_var++;
		info_struct->cmd_buf_type_var = CMD_AND;
	}
	else if (buf_var[j_var] == ';')
	{
		buf_var[j_var] = 0;
		info_struct->cmd_buf_type_var = CMD_CHAIN;
	}
	else
		return (0);
	*p_var = j_var;
	return (1);
}
/**
* check_chain_func - checks we should continue chaining based on last status
* @info_struct: the parameter struct
* @buf_var: the char buffer
* @p_var: address of current position in buf
* @i_var: starting position in buf
* @len_var: length of buf
*/
void check_chain_func(info_t *info_struct, char *buf_var,
		size_t *p_var, size_t i_var, size_t len_var)
{
	size_t j_var = *p_var;

	if (info_struct->cmd_buf_type_var == CMD_AND)
	{
		if (info_struct->status_var)
		{
			buf_var[i_var] = 0;
			j_var = len_var;
		}
	}
	if (info_struct->cmd_buf_type_var == CMD_OR)
	{
		if (!info_struct->status_var)
		{
			buf_var[i_var] = 0;
			j_var = len_var;
		}
	}
	*p_var = j_var;
}
/**
* replace_alias_func - replaces an aliases in the tokenized string
* @info_struct: the parameter struct
* Return: 1 if replaced, 0 otherwise
*/
int replace_alias_func(info_t *info_struct)
{
	int i_var;
	list_t *node_struct;
	char *p_var;

	for (i_var = 0; i_var < 10; i_var++)
	{
		node_struct = node_starts_with_func(info_struct->alias_var,
				info_struct->argv[0], '=');
		if (!node_struct)
			return (0);
		free(info_struct->argv[0]);
		p_var = _strchr_func(node_struct->str_var, '=');
		if (!p_var)
			return (0);
		p_var = _strdup_func(p_var + 1);
		if (!p_var)
			return (0);
		info_struct->argv[0] = p_var;
	}
	return (1);
}
/**
* replace_vars_func - replaces vars in the tokenized string
* @info_struct: the parameter struct
* Return: 1 if replaced, 0 otherwise
*/
int replace_vars_func(info_t *info_struct)
{
	int i_var = 0;
	list_t *node_struct;

	for (i_var = 0; info_struct->argv[i_var]; i_var++)
	{
		if (info_struct->argv[i_var][0] != '$' || !info_struct->argv[i_var][1])
			continue;

		if (!_strcmp_func(info_struct->argv[i_var], "$?"))
		{
			replace_string_func(&(info_struct->argv[i_var]),
					_strdup_func(convert_number_func
						(info_struct->status_var, 10, 0)));
			continue;
		}
		if (!_strcmp_func(info_struct->argv[i_var], "$$"))
		{
			replace_string_func(&(info_struct->argv[i_var]),
					_strdup_func(convert_number_func
						(getpid(), 10, 0)));
			continue;
		}
		node_struct = node_starts_with_func(info_struct->env_var,
				&info_struct->argv[i_var][1], '=');
		if (node_struct)
		{
			replace_string_func(&(info_struct->argv[i_var]),
					_strdup_func(_strchr_func
						(node_struct->str_var, '=') + 1));
			continue;
		}
		replace_string_func(&info_struct->argv[i_var], _strdup_func(""));

	}
	return (0);
}
/**
* replace_string_func - replaces string
* @old_var: address of old string
* @new_var: new string
* Return: 1 if replaced, 0 otherwise
*/
int replace_string_func(char **old_var, char *new_var)
{
	free(*old_var);
	*old_var = new_var;
	return (1);
}

