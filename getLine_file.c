#include "main.h"
/**
* input_buf_func - buffers chained commands
* @info_struct: parameter struct
* @buf_var: address of buffer
* @len_var: address of len var
* Return: bytes read
*/
ssize_t input_buf_func(info_t *info_struct, char **buf_var, size_t *len_var)
{
	ssize_t r_var = 0;
	size_t len_p_var = 0;

	if (!*len_var)
	{
		free(*buf_var);
		*buf_var = NULL;
		signal(SIGINT, sigintHandler_func);
#if USE_GETLINE
		r_var = getline(buff_var, &len_p_var, stdin);
#else
		r_var = _getline_func(info_struct, buf_var, &len_p_var);
#endif
		if (r_var > 0)
		{
			if ((*buf_var)[r_var - 1] == '\n')
			{
				(*buf_var)[r_var - 1] = '\0';
				r_var--;
			}
			info_struct->linecount_flag_var = 1;
			remove_comments_func(*buf_var);
			build_history_list_func(info_struct,
					*buf_var, info_struct->histcount_var++);
			{
				*len_var = r_var;
				info_struct->cmd_buf_var = buf_var;
			}
		}
	}
	return (r_var);
}
/**
* get_input_func - gets a line minus the newline
* @info_struct: parameter struct
* Return: bytes read
*/
ssize_t get_input_func(info_t *info_struct)
{
	static char *buf_var;
	static size_t i_var, j_var, len_var;
	ssize_t r_var = 0;
	char **buf_p_var = &(info_struct->arg_var), *p_var;

	_putchar_func(BUF_FLUSH);
	r_var = input_buf_func(info_struct, &buf_var, &len_var);
	if (r_var == -1)
		return (-1);
	if (len_var)
	{
		j_var = i_var;
		p_var = buf_var + i_var;

		check_chain_func(info_struct, buf_var, &j_var, i_var, len_var);
		while (j_var < len_var)
		{
			if (is_chain_func(info_struct, buf_var, &j_var))
				break;
			j_var++;
		}

		i_var = j_var + 1;
		if (i_var >= len_var)
		{
			i_var = len_var = 0;
			info_struct->cmd_buf_type_var = CMD_NORM;
		}

		*buf_p_var = p_var;
		return (_strlen_func(p_var));
	}

	*buf_p_var = buf_var;
	return (r_var);
}
/**
* read_buf_func - reads a buffer
* @info_struct: parameter struct
* @buf_var: buffer
* @i_var: size
* Return: r_var
*/
ssize_t read_buf_func(info_t *info_struct, char *buf_var, size_t *i_var)
{
	ssize_t r_var = 0;

	if (*i_var)
		return (0);
	r_var = read(info_struct->readfd_var, buf_var, READ_BUF_SIZE);
	if (r_var >= 0)
		*i_var = r_var;
	return (r_var);
}
/**
* _getline_func - gets the next line of input from STDIN
* @info_struct: parameter struct
* @ptr_var: address of pointer to buffer, preallocated or NULL
* @length_var: size of preallocated ptr buffer if not NULL
* Return: s
*/
int _getline_func(info_t *info_struct, char **ptr_var, size_t *length_var)
{
	static char buf_var[READ_BUF_SIZE];
	static size_t i_var, len_var;
	size_t k_var;
	ssize_t r_var = 0, s_var = 0;
	char *p_var = NULL, *new_p_var = NULL, *c_var;

	p_var = *ptr_var;
	if (p_var && length_var)
		s_var = *length_var;
	if (i_var == len_var)
		i_var = len_var = 0;

	r_var = read_buf_func(info_struct, buf_var, &len_var);
	if (r_var == -1 || (r_var == 0 && len_var == 0))
		return (-1);

	c_var = _strchr_func(buf_var + i_var, '\n');
	k_var = c_var ? 1 + (unsigned int)(c_var - buf_var) : len_var;
	new_p_var = _realloc_func(p_var, s_var, s_var ? s_var + k_var : k_var + 1);
	if (!new_p_var)
		return (p_var ? free(p_var), -1 : -1);

	if (s_var)
		_strncat_func(new_p_var, buf_var + i_var, k_var - i_var);
	else
		_strncpy_func(new_p_var, buf_var + i_var, k_var - i_var + 1);

	s_var += k_var - i_var;
	i_var = k_var;
	p_var = new_p_var;

	if (length_var)
		*length_var = s_var;
	*ptr_var = p_var;
	return (s_var);
}
/**
* sigintHandler_func - blocks ctrl-C
* @sig_num_var: the signal number
* Return: void
*/
void sigintHandler_func(__attribute__((unused))int sig_num_var)
{
	_puts_func("\n");
	_puts_func("$ ");
	_putchar_func(BUF_FLUSH);
}
