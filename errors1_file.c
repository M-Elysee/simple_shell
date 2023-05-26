#include "main.h"
/**
* _erratoi_func - converts a string to an integer
* @s_var: the string to be converted
* Return: 0 if no numbers in string, converted number otherwise
*       -1 on error
*/
int _erratoi_func(char *s_var)
{
	int i_var = 0;
	unsigned long int result_var = 0;

	if (*s_var == '+')
		s_var++;
	for (i_var = 0;  s_var[i_var] != '\0'; i_var++)
	{
		if (s_var[i_var] >= '0' && s_var[i_var] <= '9')
		{
			result_var *= 10;
			result_var += (s_var[i_var] - '0');
			if (result_var > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result_var);
}
/**
* print_error_func - prints an error message
* @info_struct: the parameter & return info struct
* @estr_var: string containing specified error type
* Return: 0 if no numbers in string, converted number otherwise
*        -1 on error
*/
void print_error_func(info_t *info_struct, char *estr_var)
{
	_eputs_func(info_struct->fname_var);
	_eputs_func(": ");
	print_d_func(info_struct->line_count_var, STDERR_FILENO);
	_eputs_func(": ");
	_eputs_func(info_struct->argv[0]);
	_eputs_func(": ");
	_eputs_func(estr_var);
}
/**
* print_d_func - function prints a decimal (integer) number (base 10)
* @input_var: the input
* @fd_var: the filedescriptor to write to
* Return: number of characters printed
*/
int print_d_func(int input_var, int fd_var)
{
	int (*__putchar_func)(char) = _putchar_func;
	int i_var, count_var = 0;
	unsigned int _absvar_, current_var;

	if (fd_var == STDERR_FILENO)
		__putchar_func = _eputchar_func;
	if (input_var < 0)
	{
		_absvar_ = -input_var;
		__putchar_func('-');
		count_var++;
	}
	else
		_absvar_ = input_var;
	current_var = _absvar_;
	for (i_var = 1000000000; i_var > 1; i_var /= 10)
	{
		if (_absvar_ / i_var)
		{
			__putchar_func('0' + current_var / i_var);
			count_var++;
		}
		current_var %= i_var;
	}
	__putchar_func('0' + current_var);
	count_var++;
	return (count_var);
}
/**
* convert_number_func - converter function, a clone of itoa
* @num_var: number
* @base_var: base
* @flags_var: argument flags
* Return: string
*/
char *convert_number_func(long int num_var, int base_var, int flags_var)
{
	static char *array_var;
	static char buffer_var[50];
	char sign_var = 0;
	char *ptr_var;
	unsigned long n_var = num_var;

	if (!(flags_var & CONVERT_UNSIGNED) && num_var < 0)
	{
		n_var = -num_var;
		sign_var = '-';

	}
	array_var = flags_var & CONVERT_LOWERCASE ?
		"0123456789abcdef" : "0123456789ABCDEF";
	ptr_var = &buffer_var[49];
	*ptr_var = '\0';

	do	{
		*--ptr_var = array_var[n_var % base_var];
		n_var /= base_var;
	} while (n_var != 0);

	if (sign_var)
		*--ptr_var = sign_var;
	return (ptr_var);
}
/**
* remove_comments_func - function replaces first instance of '#' with '\0'
* @buf_var: address of the string to modify
* Return: Always 0;
*/
void remove_comments_func(char *buf_var)
{
	int i_var;

	for (i_var = 0; buf_var[i_var] != '\0'; i_var++)
		if (buf_var[i_var] == '#' && (!i_var || buf_var[i_var - 1] == ' '))
		{
			buf_var[i_var] = '\0';
			break;
		}
}
