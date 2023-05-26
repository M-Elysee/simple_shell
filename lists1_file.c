#include "main.h"
/**
* list_len_func - determines length of linked list
* @h_struct: pointer to first node
* Return: size of list
*/
size_t list_len_func(const list_t *h_struct)
{
	size_t i_var = 0;

	while (h_struct)
	{
		h_struct = h_struct->next_var;
		i_var++;
	}
	return (i_var);
}
/**
* list_to_strings_func - returns an array of strings of the list->str
* @head_struct: pointer to first node
* Return: array of strings
*/
char **list_to_strings_func(list_t *head_struct)
{
	list_t *node_struct = head_struct;
	size_t i_var = list_len_func(head_struct), j_var;
	char **strs_var;
	char *str_var;

	if (!head_struct || !i_var)
		return (NULL);
	strs_var = malloc(sizeof(char *) * (i_var + 1));
	if (!strs_var)
		return (NULL);
	for (i_var = 0; node_struct;
			node_struct = node_struct->next_var, i_var++)
	{
		str_var = malloc(_strlen_func(node_struct->str_var) + 1);
		if (!str_var)
		{
			for (j_var = 0; j_var < i_var; j_var++)
				free(strs_var[j_var]);
			free(strs_var);
			return (NULL);
		}

		str_var = _strcpy_func(str_var, node_struct->str_var);
		strs_var[i_var] = str_var;
	}
	strs_var[i_var] = NULL;
	return (strs_var);
}
/**
* print_list_func - prints all elements of a list_t linked list
* @h_struct: pointer to first node
* Return: size of list
*/
size_t print_list_func(const list_t *h_struct)
{
	size_t i_var = 0;

	while (h_struct)
	{
		_puts_func(convert_number_func(h_struct->num_var, 10, 0));
		_putchar_func(':');
		_putchar_func(' ');
		_puts_func(h_struct->str_var ? h_struct->str_var : "(nil)");
		_puts_func("\n");
		h_struct = h_struct->next_var;
		i_var++;
	}
	return (i_var);
}
/**
* node_starts_with_func - returns node whose string starts with prefix
* @node_struct: pointer to list head
* @prefix_var: string to match
* @c_var: the next character after prefix to match
* Return: match node or null
*/
list_t *node_starts_with_func(list_t *node_struct,
		char *prefix_var, char c_var)
{
	char *p_var = NULL;

	while (node_struct)
	{
		p_var = starts_with_func(node_struct->str_var, prefix_var);
		if (p_var && ((c_var == -1) || (*p_var == c_var)))
			return (node_struct);
		node_struct = node_struct->next_var;
	}
	return (NULL);
}
/**
* get_node_index_func - gets the index of a node
* @head_struct: pointer to list head
* @node_struct: pointer to the node
* Return: index of node or -1
*/
ssize_t get_node_index_func(list_t *head_struct, list_t *node_struct)
{
	size_t i_var = 0;

	while (head_struct)
	{
		if (head_struct == node_struct)
			return (i_var);
		head_struct = head_struct->next_var;
		i_var++;
	}
	return (-1);
}

