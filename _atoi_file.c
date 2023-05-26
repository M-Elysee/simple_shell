#include "main.h"
/**
* interactive_func - returns true if shell is interactive mode
* @info_struct: struct address
* Return: 1 if interactive mode, 0 otherwise
*/
int interactive_func(info_t *info_struct)
{
	return (isatty(STDIN_FILENO) && info_struct->readfd_var <= 2);
}
/**
* is_delim_func - checks if character is a delimeter
* @c_var: the char to check
* @delim_var: the delimeter string
* Return: 1 if true, 0 if false
*/
int is_delim_func(char c_var, char *delim_var)
{
	while (*delim_var)
		if (*delim_var++ == c_var)
			return (1);
	return (0);
}
/**
* _isalpha_func - checks for alphabetic character
* @c_var: The character to input
* Return: 1 if c_var is alphabetic, 0 otherwise
*/
int _isalpha_func(int c_var)
{
	if ((c_var >= 'a' && c_var <= 'z') || (c_var >= 'A' && c_var <= 'Z'))
		return (1);
	else
		return (0);
}
/**
* _atoi_func - converts a string to an integer
* @s_var: the string to be converted
* Return: 0 if no numbers in string, converted number otherwise
*/
int _atoi_func(char *s_var)
{
	int i_var, sign_var = 1, flag_var = 0, output_var;
	unsigned int result_var = 0;

	for (i_var = 0; s_var[i_var] != '\0' && flag_var != 2; i_var++)
	{
		if (s_var[i_var] == '-')
			sign_var *= -1;
		if (s_var[i_var] >= '0' && s_var[i_var] <= '9')
		{
			flag_var = 1;
			result_var *= 10;
			result_var += (s_var[i_var] - '0');
		}
		else if (flag_var == 1)
			flag_var = 2;
	}
	if (sign_var == -1)
		output_var = -result_var;
	else
		output_var = result_var;
	return (output_var);
}



