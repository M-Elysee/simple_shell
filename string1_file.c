#include "main.h"
/**
* _strcpy_func - copies a string
* @dest_var: the destination
* @src_var: the source
* Return: pointer to destination
*/
char *_strcpy_func(char *dest_var, char *src_var)
{
	int i_var = 0;

	if (dest_var == src_var || src_var == 0)
		return (dest_var);
	while (src_var[i_var])
	{
		dest_var[i_var] = src_var[i_var];
		i_var++;
	}
	dest_var[i_var] = 0;
	return (dest_var);
}
/**
* _strdup_func - duplicates a string
* @str_var: the string to duplicate
* Return: pointer to the duplicated string
*/
char *_strdup_func(const char *str_var)
{
	int length_var = 0;
	char *ret_var;

	if (str_var == NULL)
		return (NULL);
	while (*str_var++)
		length_var++;
	ret_var = malloc(sizeof(char) * (length_var + 1));
	if (!ret_var)
		return (NULL);
	for (length_var++; length_var--;)
		ret_var[length_var] = *--str_var;
	return (ret_var);
}
/**
* _puts_func - prints an input string
* @str_var: the string to be printed
* Return: Nothing
*/
void _puts_func(char *str_var)
{
	int i_var = 0;

	if (!str_var)
		return;
	while (str_var[i_var] != '\0')
	{
		_putchar_func(str_var[i_var]);
		i_var++;
	}
}
/**
* _putchar_func - writes the character c to stdout
* @c_var: The character to print
* Return: On success 1.On error, -1 is returned,
* and errno is set appropriately.
*/
int _putchar_func(char c_var)
{
	static int i_var;
	static char buf_var[WRITE_BUF_SIZE];

	if (c_var == BUF_FLUSH || i_var >= WRITE_BUF_SIZE)
	{
		write(1, buf_var, i_var);
		i_var = 0;
	}
	if (c_var != BUF_FLUSH)
		buf_var[i_var++] = c_var;
	return (1);
}


