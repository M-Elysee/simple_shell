#include "main.h"
/**
* _myexit_func - exits the shell
* @info_struct: Structure containing potential arguments.
* Return: exits with a given exit status
*/
int _myexit_func(info_t *info_struct)
{
	int exitcheck_var;

	if (info_struct->argv[1])
	{
		exitcheck_var = _erratoi_func(info_struct->argv[1]);
		if (exitcheck_var == -1)
		{
			info_struct->status_var = 2;
			print_error_func(info_struct, "Illegal number: ");
			_eputs_func(info_struct->argv[1]);
			_eputchar_func('\n');
			return (1);
		}
		info_struct->err_num_var = _erratoi_func(info_struct->argv[1]);
		return (-2);
	}
	info_struct->err_num_var = -1;
	return (-2);
}
/**
* _mycd_func - changes the current directory of the process
* @info_struct: Structure containing potential arguments.
* Return: Always 0
*/
int _mycd_func(info_t *info_struct)
{
	char *s_var, *dir_var, buffer_var[1024];
	int chdir_ret_var;

	s_var = getcwd(buffer_var, 1024);
	if (!s_var)
		_puts_func("TODO: >>getcwd failure emsg here<<\n");
	if (!info_struct->argv[1])
	{
		dir_var = _getenv_func(info_struct, "HOME=");
		if (!dir_var)
			chdir_ret_var =
				chdir((dir_var = _getenv_func
							(info_struct, "PWD=")) ? dir_var : "/");
		else
			chdir_ret_var = chdir(dir_var);
	}
	else if (_strcmp_func(info_struct->argv[1], "-") == 0)
	{
		if (!_getenv_func(info_struct, "OLDPWD="))
		{
			_puts_func(s_var);
			_putchar_func('\n');
			return (1);
		}
		_puts_func(_getenv_func(info_struct, "OLDPWD=")),
			_putchar_func('\n');
		chdir_ret_var =
			chdir((dir_var = _getenv_func(info_struct,
							"OLDPWD=")) ? dir_var : "/");
	}
	else
		chdir_ret_var = chdir(info_struct->argv[1]);
	if (chdir_ret_var == -1)
	{
		print_error_func(info_struct, "can't cd to ");
		_eputs_func(info_struct->argv[1]), _eputchar_func('\n');
	}
	else
	{
		_setenv_func(info_struct, "OLDPWD",
				_getenv_func(info_struct, "PWD="));
		_setenv_func(info_struct, "PWD",
				getcwd(buffer_var, 1024));
	}
	return (0);
}
/**
* _myhelp_func - changes the current directory of the process
* @info_struct: Structure containing potential arguments.
* Return: Always 0
*/
int _myhelp_func(info_t *info_struct)
{
	char **arg_array_var;

	arg_array_var = info_struct->argv;
	_puts_func("help call works. Function not yet implemented \n");
	if (0)
		_puts_func(*arg_array_var);
	return (0);
}
