#include "main.h"
/**
* main - entry point
* @argc: arg count
* @argv: arg vector
* Return: 0 on success, 1 on error
*/
int main(int argc, char **argv)
{
	info_t info_struct[] = { INFO_INIT };
	int fd_var = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd_var)
			: "r" (fd_var));

	if (argc == 2)
	{
		fd_var = open(argv[1], O_RDONLY);
		if (fd_var == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs_func(argv[0]);
				_eputs_func(": 0: Can't open ");
				_eputs_func(argv[1]);
				_eputchar_func('\n');
				_eputchar_func(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info_struct->readfd_var = fd_var;
	}
	populate_env_list_func(info_struct);
	read_history_func(info_struct);
	hsh_func(info_struct, argv);
	return (EXIT_SUCCESS);
}
