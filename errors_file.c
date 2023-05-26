#include "main.h"
/**
* _eputs_func - prints an input string
* @str_var: the string to be printed
* Return: Nothing
*/
void _eputs_func(char *str_var)
{
	int i_var = 0;

	if (!str_var)
		return;
	while (str_var[i_var] != '\0')
	{
		_eputchar_func(str_var[i_var]);
		i_var++;
	}
}
/**
* _eputchar_func - writes the character c to stderr
* @c_var: The character to print
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _eputchar_func(char c_var)
{
	static int i_var;
	static char buf_var[WRITE_BUF_SIZE];

	if (c_var == BUF_FLUSH || i_var >= WRITE_BUF_SIZE)
	{
		write(2, buf_var, i_var);
		i_var = 0;
	}
	if (c_var != BUF_FLUSH)
		buf_var[i_var++] = c_var;
	return (1);
}
/**
* _putfd_func - writes the character c to given fd
* @c_var: The character to print
* @fd_var: The filedescriptor to write to
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _putfd_func(char c_var, int fd_var)
{
	static int i_var;
	static char buf_var[WRITE_BUF_SIZE];

	if (c_var == BUF_FLUSH || i_var >= WRITE_BUF_SIZE)
	{
		write(fd_var, buf_var, i_var);
		i_var = 0;
	}
	if (c_var != BUF_FLUSH)
		buf_var[i_var++] = c_var;
	return (1);
}
/**
* _putsfd_func - prints an input string
* @str_var: the string to be printed
* @fd_var: the filedescriptor to write to
* Return: the number of chars put
*/
int _putsfd_func(char *str_var, int fd_var)
{
	int i_var = 0;

	if (!str_var)
		return (0);
	while (*str_var)
	{
		i_var += _putfd_func(*str_var++, fd_var);
	}
	return (i_var);
}

