#include "main.h"
/**
*_strncpy_func - copies a string
*@dest_var: the destination string to be copied to
*@src_var: the source string
*@n_var: the amount of characters to be copied
*Return: the concatenated string
*/
char *_strncpy_func(char *dest_var, char *src_var, int n_var)
{
	int i_var, j_var;
	char *s_var = dest_var;

	i_var = 0;
	while (src_var[i_var] != '\0' && i_var < n_var - 1)
	{
		dest_var[i_var] = src_var[i_var];
		i_var++;
	}
	if (i_var < n_var)
	{
		j_var = i_var;
		while (j_var < n_var)
		{
			dest_var[j_var] = '\0';
			j_var++;
		}
	}
	return (s_var);
}
/**
*_strncat_func - concatenates two strings
*@dest_var: the first string
*@src_var: the second string
*@n_var: the amount of bytes to be maximally used
*Return: the concatenated string
*/
char *_strncat_func(char *dest_var, char *src_var, int n_var)
{
	int i_var, j_var;
	char *s_var = dest_var;

	i_var = 0;
	j_var = 0;
	while (dest_var[i_var] != '\0')
		i_var++;
	while (src_var[j_var] != '\0' && j_var < n_var)
	{
		dest_var[i_var] = src_var[j_var];
		i_var++;
		j_var++;
	}
	if (j_var < n_var)
		dest_var[i_var] = '\0';
	return (s_var);
}
/**
*_strchr_func - locates a character in a string
*@s_var: the string to be parsed
*@c_var: the character to look for
*Return: (s_var) a pointer to the memory area s_var
*/
char *_strchr_func(char *s_var, char c_var)
{
	do {
		if (*s_var == c_var)
			return (s_var);
	} while (*s_var++ != '\0');
	return (NULL);
}


