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

extern char **environ;
char *nme;
int hst;

/**
 * struct list_s - A new struct define a linked list.
 * @dir: A current directory path.
 * @next: A pointer to next struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *nxt;
} list_t;

/**
 * struct alias_s - A new struct define alias.
 * @nme: The name of the alias.
 * @val: The value of the alias.
 * @nxt: pointer to next struct alias_s.
 */
typedef struct alias_s
{
	char *val;
	char *nme;
	struct alias_s *nxt;
} alias_t;

alias_t *alias;


/**
 * struct builtin_s - new struct define built-in commands.
 * @name: name of the built-in command.
 * @f: function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	int (*f)(char **av, char **frnt);
	char *nme;
} builtin_t;

void handle_line(char **lne, ssize_t rread);
ssize_t g_n_len(char *lne);
void logic_op(char *lne, ssize_t *n_len);
void var_replace(char **ag, int *ex_retn);
char *g_ag(char *lne, int *ex_retn);
int call_ag(char **ag, char **frnt, int *ex_retn);
int run_ag(char **ag, char **frnt, int *ex_retn);
int handle_ag(int *ex_retn);
int check_ag(char **ag);
void fre_ag(char **ag, char **frnt);
char **replace_alias(char **ag);

void hlp_setenv(void);
void hlp_unsetenv(void);
void hlp_exit(void);
void hlp_help(void);
void hlp_history(void);
void hlp_all(void);
void hlp_alias(void);
void hlp_cd(void);
void hlp_env(void);

char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

char *g_location(char *cmd);
list_t *g_path_dir(char *path);
int execute(char **ag, char **frnt);
void fre_list(list_t *hd);
void *_realloc(void *pnt, unsigned int o_size, unsigned int n_size);
ssize_t _getline(char **lpnt, size_t *n, FILE *r_stream);
char **_strtok(char *lne, char *delim);
char *_itoa(int nmb);

int (*get_builtin(char *cmd))(char **ag, char **frnt);
int shell_cmd_exit(char **ag, char **front);
int shell_cmd_setenv(char **ag, char __attribute__((__unused__)) **frnt);
int shell_cmd_unsetenv(char **ag, char __attribute__((__unused__)) **frnt);
int shell_cmd_cd(char **ag, char __attribute__((__unused__)) **frnt);
int shell_cmd_alias(char **ag, char __attribute__((__unused__)) **frnt);
int shell_cmd_env(char **ag, char __attribute__((__unused__)) **frnt);
void set_alias(char *var_nme, char *val);
void print_alias(alias_t *alias);
int shell_cmd_hlp(char **ag, char __attribute__((__unused__)) **frnt);


char **_cpenv(void);
void fre_env(void);
char **_getenv(const char *var);

int create_error(char **ag, int err);
char *error_env(char **ag);
char *error_1(char **ag);
char *error_2_exit(char **ag);
char *error_2_cd(char **ag);
char *error_2_syntax(char **ag);
char *error_126(char **ag);
char *error_127(char **ag);

alias_t *add_alias_end(alias_t **hd, char *nme, char *val);
void fre_alias_list(alias_t *hd);
list_t *add_node_end(list_t **hd, char *dir);
void fre_list(list_t *hd);


int proc_file_commands(char *f_path, int *ex_retn);
#endif /* _SHELL_H_ */
