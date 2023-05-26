#include "main.h"
/**
* clear_info_func - initializes info_t struct
* @info_struct: struct address
*/
void clear_info_func(info_t *info_struct)
{
	info_struct->arg_var = NULL;
	info_struct->argv = NULL;
	info_struct->path_var = NULL;
	info_struct->argc = 0;
}
/**
* set_info_func - initializes info_t struct
* @info_struct: struct address
* @av_var: argument vector
*/
void set_info_func(info_t *info_struct, char **av_var)
{
	int i_var = 0;

	info_struct->fname_var = av_var[0];
	if (info_struct->arg_var)
	{
		info_struct->argv = strtow_func(info_struct->arg_var, " \t");
		if (!info_struct->argv)
		{
			info_struct->argv = malloc(sizeof(char *) * 2);
			if (info_struct->argv)
			{
				info_struct->argv[0] =
					_strdup_func(info_struct->arg_var);
				info_struct->argv[1] = NULL;
			}
		}
		for (i_var = 0; info_struct->argv && info_struct->argv[i_var]; i_var++)
			;
		info_struct->argc = i_var;

		replace_alias_func(info_struct);
		replace_vars_func(info_struct);
	}
}
/**
* free_info_func - frees info_t struct fields
* @info_struct: struct address
* @all_var: true if freeing all fields
*/
void free_info_func(info_t *info_struct, int all_var)
{
	ffree_func(info_struct->argv);
	info_struct->argv = NULL;
	info_struct->path_var = NULL;
	if (all_var)
	{
		if (!info_struct->cmd_buf_var)
			free(info_struct->arg_var);
		if (info_struct->env_var)
			free_list_func(&(info_struct->env_var));
		if (info_struct->history_var)
			free_list_func(&(info_struct->history_var));
		if (info_struct->alias_var)
			free_list_func(&(info_struct->alias_var));
		ffree_func(info_struct->environ);
			info_struct->environ = NULL;
		bfree_func((void **)info_struct->cmd_buf_var);
		if (info_struct->readfd_var > 2)
			close(info_struct->readfd_var);
		_putchar_func(BUF_FLUSH);
	}
}

