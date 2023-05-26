#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for_command_chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for_convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1_if_using_system_getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
* struct liststr_struct - singly linked list
* @num_var: the number field
* @str_var: a string
* @next_var: points to the next node
*/
typedef struct liststr_struct
{
	int num_var;
	char *str_var;
	struct liststr_struct *next_var;
} list_t;

/**
* struct passinfo_struct - contains pseudo-arguements to pass into a function
* @arg_var: a string generated from getline containing arguements
* @argv:an array of strings generated from arg
* @path_var: a string path for the current command
* @argc: the argument count
* @line_count_var: the error count
* @err_num_var: the error code for exit()s
* @linecount_flag_var: if on count this line of input
* @fname_var: the program filename
* @env_var: linked list local copy of environ
* @environ: custom modified copy of environ from LL env
* @history_var: the history node
* @alias_var: the alias node
* @env_changed_var: on if environ was changed
* @status_var: the return status of the last exec'd command
* @cmd_buf_var: address of pointer to cmd_buf, on if chaining
* @cmd_buf_type_var: CMD_type ||, &&, ;
* @readfd_var: the fd from which to read line input
* @histcount_var: the history line number count
*/
typedef struct passinfo_struct
{
	char *arg_var;
	char **argv;
	char *path_var;
	int argc;
	unsigned int line_count_var;
	int err_num_var;
	int linecount_flag_var;
	char *fname_var;
	list_t *env_var;
	list_t *history_var;
	list_t *alias_var;
	char **environ;
	int env_changed_var;
	int status_var;

	char **cmd_buf_var;
	int cmd_buf_type_var;
	int readfd_var;
	int histcount_var;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
* struct builtin_struct - contains a builtin string and related function
* @type_var: the builtin command flag
* @func_var: the function
*/
typedef struct builtin_struct
{
	char *type_var;
	int (*func_var)(info_t *);
} builtin_table;


/* _shloop_file.c */
int hsh_func(info_t *, char **);
int find_builtin_func(info_t *);
void find_cmd_func(info_t *);
void fork_cmd_func(info_t *);

/* toem_parser_file.c */
int is_cmd_func(info_t *, char *);
char *dup_chars_func(char *, int, int);
char *find_path_func(info_t *, char *, char *);

/* loophsh_file.c */
int loophsh_func(char **);

/* toem_errors_file.c */
void _eputs_func(char *);
int _eputchar_func(char);
int _putfd_func(char c_var, int fd_var);
int _putsfd_func(char *str_var, int fd_var);

/* toem_string_file.c */
int _strlen_func(char *);
int _strcmp_func(char *, char *);
char *starts_with_func(const char *, const char *);
char *_strcat_func(char *, char *);

/* toem_string1_file.c */
char *_strcpy_func(char *, char *);
char *_strdup_func(const char *);
void _puts_func(char *);
int _putchar_func(char);

/* toem_exits_file.c */
char *_strncpy_func(char *, char *, int);
char *_strncat_func(char *, char *, int);
char *_strchr_func(char *, char);

/* toem_tokenizer_file.c */
char **strtow_func(char *, char *);
char **strtow2_func(char *, char);

/* toem_realloc_file.c */
char *_memset_func(char *, char, unsigned int);
void ffree_func(char **);
void *_realloc_func(void *, unsigned int, unsigned int);

/* toem_memory_file.c */
int bfree_func(void **);

/* toem_atoi_file.c */
int interactive_func(info_t *);
int is_delim_func(char, char *);
int _isalpha_func(int);
int _atoi_func(char *);

/* toem_errors1_file.c */
int _erratoi_func(char *);
void print_error_func(info_t *, char *);
int print_d_func(int, int);
char *convert_number_func(long int, int, int);
void remove_comments_func(char *);

/* toem_builtin_file.c */
int _myexit_func(info_t *);
int _mycd_func(info_t *);
int _myhelp_func(info_t *);

/* toem_builtin1_file.c */
int _myhistory_func(info_t *);
int _myalias_func(info_t *);

/*toem_getline_file.c */
ssize_t get_input_func(info_t *);
int _getline_func(info_t *, char **, size_t *);
void sigintHandler_func(int);

/* toem_getinfo_file.c */
void clear_info_func(info_t *);
void set_info_func(info_t *, char **);
void free_info_func(info_t *, int);

/* toem_environ_file.c */
char *_getenv_func(info_t *, const char *);
int _myenv_func(info_t *);
int _mysetenv_func(info_t *);
int _myunsetenv_func(info_t *);
int populate_env_list_func(info_t *);

/* toem_getenv_file.c */
char **get_environ_func(info_t *);
int _unsetenv_func(info_t *, char *);
int _setenv_func(info_t *, char *, char *);

/* toem_history_file.c */
char *get_history_file_func(info_t *info);
int write_history_func(info_t *info);
int read_history_func(info_t *info);
int build_history_list_func(info_t *info, char *buf, int linecount);
int renumber_history_func(info_t *info);

/* toem_lists_file.c */
list_t *add_node_func(list_t **, const char *, int);
list_t *add_node_end_func(list_t **, const char *, int);
size_t print_list_str_func(const list_t *);
int delete_node_at_index_func(list_t **, unsigned int);
void free_list_func(list_t **);

/* toem_lists1_file.c */
size_t list_len_func(const list_t *);
char **list_to_strings_func(list_t *);
size_t print_list_func(const list_t *);
list_t *node_starts_with_func(list_t *, char *, char);
ssize_t get_node_index_func(list_t *, list_t *);

/* toem_vars_file.c */
int is_chain_func(info_t *, char *, size_t *);
void check_chain_func(info_t *, char *, size_t *, size_t, size_t);
int replace_alias_func(info_t *);
int replace_vars_func(info_t *);
int replace_string_func(char **, char *);

#endif

