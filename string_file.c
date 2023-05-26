#include "main.h"
/**
* _strlen_func - returns the length of a string
* @s_var: the string whose length to check
* Return: integer length of string
*/
int _strlen_func(char *s_var)
{
	int i_var = 0;

	if (!s_var)
		return (0);

	while (*s_var++)
		i_var++;
	return (i_var);
}
/**
* _strcmp_func - performs lexicogarphic comparison of two strangs.
* @s1_var: the first strang
* @s2_var: the second strang
* Return: negative if s1_var < s2_var,
* positive if s1_var > s2_var, zero if s1_var == s2_var
*/
int _strcmp_func(char *s1_var, char *s2_var)
{
	while (*s1_var && *s2_var)
	{
		if (*s1_var != *s2_var)
			return (*s1_var - *s2_var);
		s1_var++;
		s2_var++;
	}
	if (*s1_var == *s2_var)
		return (0);
	else
		return (*s1_var < *s2_var ? -1 : 1);
}
/**
* starts_with_func - checks if needle starts with haystack
* @haystack_var: string to search
* @needle_var: the substring to find
* Return: address of next char of haystack or NULL
*/
char *starts_with_func(const char *haystack_var, const char *needle_var)
{
	while (*needle_var)
		if (*needle_var++ != *haystack_var++)
			return (NULL);
	return ((char *)haystack_var);
}
/**
* _strcat_func - concatenates two strings
* @dest_var: the destination buffer
* @src_var: the source buffer
* Return: pointer to destination buffer
*/
char *_strcat_func(char *dest_var, char *src_var)
{
	char *ret_var = dest_var;

	while (*dest_var)
		dest_var++;
	while (*src_var)
		*dest_var++ = *src_var++;
	*dest_var = *src_var;
	return (ret_var);
}

