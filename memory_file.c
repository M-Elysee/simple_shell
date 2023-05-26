#include "main.h"
/**
* bfree_func - frees a pointer and NULLs the address
* @ptr_var: address of the pointer to free
* Return: 1 if freed, otherwise 0.
*/
int bfree_func(void **ptr_var)
{
	if (ptr_var && *ptr_var)
	{
		free(*ptr_var);
		*ptr_var = NULL;
		return (1);
	}
	return (0);
}

