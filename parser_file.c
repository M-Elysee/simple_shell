#include "main.h"
/**
* is_cmd_func - determines if a file is an executable command
* @info_struct: the info struct
* @path_var: path to the file
* Return: 1 if true, 0 otherwise
*/
int is_cmd_func(info_t *info_struct, char *path_var)
{
	struct stat st_struct;

	(void)info_struct;
	if (!path_var || stat(path_var, &st_struct))
		return (0);

	if (st_struct.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
* dup_chars_func - duplicates characters
* @pathstr_var: the PATH string
* @start_var: starting index
* @stop_var: stopping index
* Return: pointer to new buffer
*/
char *dup_chars_func(char *pathstr_var, int start_var, int stop_var)
{
	static char buf_var[1024];
	int i_var = 0, k_var = 0;

	for (k_var = 0, i_var = start_var; i_var < stop_var; i_var++)
		if (pathstr_var[i_var] != ':')
			buf_var[k_var++] = pathstr_var[i_var];
	buf_var[k_var] = 0;
	return (buf_var);
}
/**
* find_path_func - finds this cmd in the PATH string
* @info_struct: the info struct
* @pathstr_var: the PATH string
* @cmd_var: the cmd to find
* Return: full path of cmd if found or NULL
*/
char *find_path_func(info_t *info_struct, char *pathstr_var, char *cmd_var)
{
	int i_var = 0, curr_pos_var = 0;
	char *path_var;

	if (!pathstr_var)
		return (NULL);
	if ((_strlen_func(cmd_var) > 2) && starts_with_func(cmd_var, "./"))
	{
		if (is_cmd_func(info_struct, cmd_var))
			return (cmd_var);
	}
	while (1)
	{
		if (!pathstr_var[i_var] || pathstr_var[i_var] == ':')
		{
			path_var = dup_chars_func(pathstr_var, curr_pos_var, i_var);
			if (!*path_var)
				_strcat_func(path_var, cmd_var);
			else
			{
				_strcat_func(path_var, "/");
				_strcat_func(path_var, cmd_var);
			}
			if (is_cmd_func(info_struct, path_var))
				return (path_var);
			if (!pathstr_var[i_var])
				break;
			curr_pos_var = i_var;
		}
		i_var++;
	}
	return (NULL);
}
