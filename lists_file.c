#include "main.h"
/**
* add_node_func - adds a node to the start of the list
* @head_struct: address of pointer to head node
* @str_var: str field of node
* @num_var: node index used by history
* Return: size of list
*/
list_t *add_node_func(list_t **head_struct, const char *str_var, int num_var)
{
	list_t *new_head_struct;

	if (!head_struct)
		return (NULL);
	new_head_struct = malloc(sizeof(list_t));
	if (!new_head_struct)
		return (NULL);
	_memset_func((void *)new_head_struct, 0, sizeof(list_t));
	new_head_struct->num_var = num_var;
	if (str_var)
	{
		new_head_struct->str_var = _strdup_func(str_var);
		if (!new_head_struct->str_var)
		{
			free(new_head_struct);
			return (NULL);
		}
	}
	new_head_struct->next_var = *head_struct;
	*head_struct = new_head_struct;
	return (new_head_struct);
}
/**
* add_node_end_func - adds a node to the end of the list
* @head_struct: address of pointer to head node
* @str_var: str field of node
* @num_var: node index used by history
* Return: size of list
*/
list_t *add_node_end_func(list_t **head_struct,
		const char *str_var, int num_var)
{
	list_t *new_node_struct, *node_struct;

	if (!head_struct)
		return (NULL);

	node_struct = *head_struct;
	new_node_struct = malloc(sizeof(list_t));
	if (!new_node_struct)
		return (NULL);
	_memset_func((void *)new_node_struct, 0, sizeof(list_t));
	new_node_struct->num_var = num_var;
	if (str_var)
	{
		new_node_struct->str_var = _strdup_func(str_var);
		if (!new_node_struct->str_var)
		{
			free(new_node_struct);
			return (NULL);
		}
	}
	if (node_struct)
	{
		while (node_struct->next_var)
			node_struct = node_struct->next_var;
		node_struct->next_var = new_node_struct;
	}
	else
		*head_struct = new_node_struct;
	return (new_node_struct);
}
/**
* print_list_str_func - prints only the str element of a list_t linked list
* @h_struct: pointer to first node
* Return: size of list
*/
size_t print_list_str_func(const list_t *h_struct)
{
	size_t i_var = 0;

	while (h_struct)
	{
		_puts_func(h_struct->str_var ? h_struct->str_var : "(nil)");
		_puts_func("\n");
		h_struct = h_struct->next_var;
		i_var++;
	}
	return (i_var);
}
/**
* delete_node_at_index_func - deletes node at given index
* @head_struct: address of pointer to first node
* @index_var: index of node to delete
* Return: 1 on success, 0 on failure
*/
int delete_node_at_index_func(list_t **head_struct, unsigned int index_var)
{
	list_t *node_struct, *prev_node_struct;
	unsigned int i_var = 0;

	if (!head_struct || !*head_struct)
		return (0);

	if (!index_var)
	{
		node_struct = *head_struct;
		*head_struct = (*head_struct)->next_var;
		free(node_struct->str_var);
		free(node_struct);
		return (1);
	}
	node_struct = *head_struct;
	while (node_struct)
	{
		if (i_var == index_var)
		{
			prev_node_struct->next_var = node_struct->next_var;
			free(node_struct->str_var);
			free(node_struct);
			return (1);
		}
		i_var++;
		prev_node_struct = node_struct;
		node_struct = node_struct->next_var;
	}
	return (0);
}
/**
* free_list_func - frees all nodes of a list
* @head_ptr_struct: address of pointer to head node
* Return: void
*/
void free_list_func(list_t **head_ptr_struct)
{
	list_t *node_struct, *next_node_struct, *head_struct;

	if (!head_ptr_struct || !*head_ptr_struct)
		return;
	head_struct = *head_ptr_struct;
	node_struct = head_struct;
	while (node_struct)
	{
		next_node_struct = node_struct->next_var;
		free(node_struct->str_var);
		free(node_struct);
		node_struct = next_node_struct;
	}
	*head_ptr_struct = NULL;
}
