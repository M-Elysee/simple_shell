#include "main.h"
/**
* hsh_func - main shell loop
* @info_struct: the parameter & return info struct
* @av_var: the argument vector from main()
* Return: 0 on success, 1 on error, or error code
*/
int hsh_func(info_t *info_struct, char **av_var)
{
	ssize_t r_var = 0;
	int builtin_ret_var = 0;

	while (r_var != -1 && builtin_ret_var != -2)
	{
		clear_info_func(info_struct);
		if (interactive_func(info_struct))
			_puts_func("$ ");
		_eputchar_func(BUF_FLUSH);
		r_var = get_input_func(info_struct);
		if (r_var != -1)
		{
			set_info_func(info_struct, av_var);
			builtin_ret_var = find_builtin_func(info_struct);
			if (builtin_ret_var == -1)
				find_cmd_func(info_struct);
		}
		else if (interactive_func(info_struct))
			_putchar_func('\n');
		free_info_func(info_struct, 0);
	}
	write_history_func(info_struct);
	free_info_func(info_struct, 1);
	if (!interactive_func(info_struct) && info_struct->status_var)
		exit(info_struct->status_var);
	if (builtin_ret_var == -2)
	{
		if (info_struct->err_num_var == -1)
			exit(info_struct->status_var);
		exit(info_struct->err_num_var);
	}
	return (builtin_ret_var);
}
/**
* find_builtin_func - finds a builtin command
* @info_struct: the parameter & return info struct
* Return: -1 if builtin not found,0 if builtin executed,
* 1 if builtin found,2 on exit()
*/
int find_builtin_func(info_t *info_struct)
{
	int i_var, built_in_ret_var = -1;
	builtin_table builtintbl_var[] = {
		{"exit", _myexit_func},
		{"env", _myenv_func},
		{"help", _myhelp_func},
		{"history", _myhistory_func},
		{"setenv", _mysetenv_func},
		{"unsetenv", _myunsetenv_func},
		{"cd", _mycd_func},
		{"alias", _myalias_func},
		{NULL, NULL}
	};

	for (i_var = 0; builtintbl_var[i_var].type_var; i_var++)
		if (_strcmp_func(info_struct->argv[0],
					builtintbl_var[i_var].type_var) == 0)
		{
			info_struct->line_count_var++;
			built_in_ret_var =
				builtintbl_var[i_var].func_var(info_struct);
			break;
		}
	return (built_in_ret_var);
}
/**
* find_cmd_func - finds a command in PATH
* @info_struct: the parameter & return info struct
* Return: void
*/
void find_cmd_func(info_t *info_struct)
{
	char *path_var = NULL;
	int i_var, k_var;

	info_struct->path_var = info_struct->argv[0];
	if (info_struct->linecount_flag_var == 1)
	{
		info_struct->line_count_var++;
		info_struct->linecount_flag_var = 0;
	}
	for (i_var = 0, k_var = 0; info_struct->arg_var[i_var]; i_var++)
		if (!is_delim_func(info_struct->arg_var[i_var], " \t\n"))
			k_var++;
	if (!k_var)
		return;

	path_var = find_path_func(info_struct,
			_getenv_func(info_struct, "PATH="), info_struct->argv[0]);
	if (path_var)
	{
		info_struct->path_var = path_var;
		fork_cmd_func(info_struct);
	}
	else
	{
		if ((interactive_func(info_struct)
					|| _getenv_func(info_struct, "PATH=")
					|| info_struct->argv[0][0] == '/')
				&& is_cmd_func(info_struct,
					info_struct->argv[0]))
			fork_cmd_func(info_struct);
		else if (*(info_struct->arg_var) != '\n')
		{
			info_struct->status_var = 127;
			print_error_func(info_struct, "not found\n");
		}
	}
}
/**
* fork_cmd_func - forks a an exec thread to run cmd
* @info_struct: the parameter & return info struct
*/
void fork_cmd_func(info_t *info_struct)
{
	pid_t child_pid_var;

	child_pid_var = fork();
	if (child_pid_var == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid_var == 0)
	{
		if (execve(info_struct->path_var,
					info_struct->argv,
					get_environ_func(info_struct)) == -1)
		{
			free_info_func(info_struct, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info_struct->status_var));
		if (WIFEXITED(info_struct->status_var))
		{
			info_struct->status_var =
				WEXITSTATUS(info_struct->status_var);
			if (info_struct->status_var == 126)
				print_error_func(info_struct,
						"Permission denied\n");
		}
	}
}

