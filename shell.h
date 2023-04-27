#ifndef _SHELL_H_
#define _SHELL_H_


#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt */
extern char **environ;
/* Global program name */
char *name;
/* Global history counter */
int hist;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A current directory path.
 * @next: A pointer to next struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct built-in_s - A new struct type defining built-in commands.
 * @name: The name of the built-in command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **av, char **frnt);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* Input Helpers */
void handle_line(char **lne, ssize_t rread);
ssize_t get_new_len(char *lne);
void logical_ops(char *lne, ssize_t *n_len);
void variable_replacement(char **ag, int *exe_retn);
char *get_args(char *lne, int *exe_retn);
int call_args(char **ag, char **front, int *exe_retn);
int run_args(char **ag, char **front, int *exe_retn);
int handle_args(int *exe_retn);
int check_args(char **ag);
void free_args(char **args, char **front);
char **replace_aliases(char **ag);

void hlp_setenv(void);
void hlp_unsetenv(void);
void hlp_exit(void);
void hlp_help(void);
void hlp_history(void);
void hlp_all(void);
void hlp_alias(void);
void hlp_cd(void);
void hlp_env(void);

/* String functions */
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/* Main Helpers */
char *g_location(char *command);
list_t *g_path_dir(char *path);
int execute(char **ag, char **front);
void fre_list(list_t *head);
void *_realloc(void *pnt, unsigned int o_size, unsigned int n_size);
ssize_t _getline(char **lpnt, size_t *n, FILE *r_stream);
char **_strtok(char *lne, char *delim);
char *_itoa(int num);

/* Builtins */
int (*get_builtin(char *command))(char **ag, char **frnt);
int shell_cmd_exit(char **ag, char **front);
int shell_cmd_setenv(char **ag, char __attribute__((__unused__)) **frnt);
int shell_cmd_unsetenv(char **ag, char __attribute__((__unused__)) **frnt);
int shell_cmd_cd(char **ag, char __attribute__((__unused__)) **frnt);
int shell_cmd_alias(char **ag, char __attribute__((__unused__)) **frnt);
int shell_cmd_env(char **ag, char __attribute__((__unused__)) **frnt);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);
int shell_cmd_hlp(char **ag, char __attribute__((__unused__)) **frnt);


/* Builtin Helpers */
char **_cpenv(void);
void fre_env(void);
char **_getenv(const char *var);

/* Error Handling */
int create_error(char **ag, int err);
char *error_env(char **ag);
char *error_1(char **ag);
char *error_2_exit(char **ag);
char *error_2_cd(char **ag);
char *error_2_syntax(char **ag);
char *error_126(char **ag);
char *error_127(char **ag);

/* Linkedlist Helpers */
alias_t *add_alias_end(alias_t **hd, char *nme, char *val);
void fre_alias_list(alias_t *hd);
list_t *add_node_end(list_t **hd, char *dir);
void fre_list(list_t *hd);


int proc_file_commands(char *f_path, int *exe_retn);
#endif /* _SHELL_H_ */
