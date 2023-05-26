#include "main.h"
/**
* get_history_file_func - gets the history file
* @info_struct: parameter struct
* Return: allocated string containg history file
*/
char *get_history_file_func(info_t *info_struct)
{
	char *buf_var, *dir_var;

	dir_var = _getenv_func(info_struct, "HOME=");
	if (!dir_var)
		return (NULL);
	buf_var = malloc(sizeof(char) * (_strlen_func(dir_var) +
				_strlen_func(HIST_FILE) + 2));
	if (!buf_var)
		return (NULL);
	buf_var[0] = 0;
	_strcpy_func(buf_var, dir_var);
	_strcat_func(buf_var, "/");
	_strcat_func(buf_var, HIST_FILE);
	return (buf_var);
}
/**
* write_history_func - creates a file, or appends to an existing file
* @info_struct: the parameter struct
* Return: 1 on success, else -1
*/
int write_history_func(info_t *info_struct)
{
	ssize_t fd_var;
	char *filename_var = get_history_file_func(info_struct);
	list_t *node_struct = NULL;

	if (!filename_var)
		return (-1);

	fd_var = open(filename_var, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename_var);
	if (fd_var == -1)
		return (-1);
	for (node_struct = info_struct->history_var;
			node_struct; node_struct = node_struct->next_var)
	{
		_putsfd_func(node_struct->str_var, fd_var);
		_putfd_func('\n', fd_var);
	}
	_putfd_func(BUF_FLUSH, fd_var);
	close(fd_var);
	return (1);
}
/**
* read_history_func - reads history from file
* @info_struct: the parameter struct
* Return: histcount on success, 0 otherwise
*/
int read_history_func(info_t *info_struct)
{
	int i_var, last_var = 0, linecount_var = 0;
	ssize_t fd_var, rdlen_var, fsize_var = 0;
	struct stat st_struct;
	char *buf_var = NULL, *filename_var = get_history_file_func(info_struct);

	if (!filename_var)
		return (0);
	fd_var = open(filename_var, O_RDONLY);
	free(filename_var);
	if (fd_var == -1)
		return (0);
	if (!fstat(fd_var, &st_struct))
		fsize_var = st_struct.st_size;
	if (fsize_var < 2)
		return (0);
	buf_var = malloc(sizeof(char) * (fsize_var + 1));
	if (!buf_var)
		return (0);
	rdlen_var = read(fd_var, buf_var, fsize_var);
	buf_var[fsize_var] = 0;
	if (rdlen_var <= 0)
		return (free(buf_var), 0);
	close(fd_var);
	for (i_var = 0; i_var < fsize_var; i_var++)
		if (buf_var[i_var] == '\n')
		{
			buf_var[i_var] = 0;
			build_history_list_func(info_struct,
					buf_var + last_var, linecount_var++);
			last_var = i_var + 1;
		}
	if (last_var != i_var)
		build_history_list_func(info_struct,
				buf_var + last_var, linecount_var++);
	free(buf_var);
	info_struct->histcount_var = linecount_var;
	while (info_struct->histcount_var-- >= HIST_MAX)
		delete_node_at_index_func(&(info_struct->history_var), 0);
	renumber_history_func(info_struct);
	return (info_struct->histcount_var);
}
/**
* build_history_list_func - adds entry to a history linked list
* @info_struct: Structure containing potential arguments.
* @buf_var: buffer
* @linecount_var: the history linecount, histcount
* Return: Always 0
*/
int build_history_list_func(info_t *info_struct,
		char *buf_var, int linecount_var)
{
	list_t *node_struct = NULL;

	if (info_struct->history_var)
		node_struct = info_struct->history_var;
	add_node_end_func(&node_struct, buf_var, linecount_var);

	if (!info_struct->history_var)
		info_struct->history_var = node_struct;
	return (0);
}
/**
* renumber_history_func - renumbers the history linked list after changes
* @info_struct: Structure containing potential arguments. Used to maintain
* Return: the new histcount
*/
int renumber_history_func(info_t *info_struct)
{
	list_t *node_struct = info_struct->history_var;
	int i_var = 0;

	while (node_struct)
	{
		node_struct->num_var = i_var++;
		node_struct = node_struct->next_var;
	}
	return (info_struct->histcount_var = i_var);
}

