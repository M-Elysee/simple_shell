#include "main.h"
/**
* _memset_func - fills memory with a constant byte
* @s_var: the pointer to the memory area
* @b_var: the byte to fill *s with
* @n_var: the amount of bytes to be filled
* Return: (s_var) a pointer to the memory area s
*/
char *_memset_func(char *s_var, char b_var, unsigned int n_var)
{
	unsigned int i_var;

	for (i_var = 0; i_var < n_var; i_var++)
		s_var[i_var] = b_var;
	return (s_var);
}
/**
* ffree_func - frees a string of strings
* @pp_var: string of strings
*/
void ffree_func(char **pp_var)
{
	char **a_var = pp_var;

	if (!pp_var)
		return;
	while (*pp_var)
		free(*pp_var++);
	free(a_var);
}
/**
* _realloc_func - reallocates a block of memory
* @ptr_var: pointer to previous malloc'ated block
* @old_size_var: byte size of previous block
* @new_size_var: byte size of new block
* Return: pointer to da ol'block nameen.
*/
void *_realloc_func(void *ptr_var, unsigned int old_size_var,
		unsigned int new_size_var)
{
	char *p_var;

	if (!ptr_var)
		return (malloc(new_size_var));
	if (!new_size_var)
		return (free(ptr_var), NULL);
	if (new_size_var == old_size_var)
		return (ptr_var);

	p_var = malloc(new_size_var);
	if (!p_var)
		return (NULL);

	old_size_var = old_size_var < new_size_var ? old_size_var : new_size_var;
	while (old_size_var--)
		p_var[old_size_var] = ((char *)ptr_var)[old_size_var];
	free(ptr_var);
	return (p_var);
}
