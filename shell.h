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
 * struct lst_s - new struct define a linked list.
 * @dir: current directory path.
 * @nxt: pointer to next struct lst_s.
 */
typedef struct lst_s
{
	char *dir;
	struct lst_s *nxt;
} lst_t;

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
 * @f: function pointer to the built-in command's function.
 */
typedef struct builtin_s
{
	int (*f)(char **av, char **frnt);
	char *nme;
} builtin_t;

void hndl_lne(char **lne, ssize_t rread);
ssize_t g_n_ln(char *lne);
void logic_op(char *lne, ssize_t *n_len);
void var_replace(char **ag, int *ex_retn);
char *g_ag(char *lne, int *ex_retn);
int call_ag(char **ag, char **frnt, int *ex_retn);
int run_ag(char **ag, char **frnt, int *ex_retn);
int hndl_ag(int *ex_retn);
int check_ag(char **ag);
void fre_ag(char **ag, char **frnt);
char **rep_alias(char **ag);

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
lst_t *g_path_dir(char *path);
void sg_hndl(int sg);
int execute(char **ag, char **frnt);
void fre_lst(lst_t *hd);
void *_realloc(void *pnt, unsigned int o_size, unsigned int n_size);
ssize_t _getline(char **lpnt, size_t *n, FILE *r_stream);
void chg_lpnt(char **lpnt, size_t *n, char *buf, size_t bsize);
char **_strtok(char *lne, char *delim);
int tok_ln(char *str, char *delim);
int cnt_tok(char *str, char *delim);
char *_itoa(int nmb);

int (*g_builtin(char *cmd))(char **ag, char **frnt);
int shell_cmd_exit(char **ag, char **frnt);
int shell_cmd_setenv(char **ag, char __attribute__((__unused__)) **frnt);
int shell_cmd_unsetenv(char **ag, char __attribute__((__unused__)) **frnt);
int shell_cmd_cd(char **ag, char __attribute__((__unused__)) **frnt);
int shell_cmd_alias(char **ag, char __attribute__((__unused__)) **frnt);
int shell_cmd_env(char **ag, char __attribute__((__unused__)) **frnt);
void st_alias(char *var_nme, char *val);
void pr_alias(alias_t *alias);
int shell_cmd_hlp(char **ag, char __attribute__((__unused__)) **frnt);
char *g_env_val(char *begin, int ln);

char **_cpenv(void);
void fre_env(void);
char **_getenv(const char *var);

int cr_err(char **ag, int err);
char *err_env(char **ag);
char *err_1(char **ag);
char *err_2_exit(char **ag);
char *err_2_cd(char **ag);
char *err_2_synt(char **ag);
char *err_126(char **ag);
char *err_127(char **ag);

alias_t *add_aliasend(alias_t **hd, char *nme, char *val);
void fre_alias_lst(alias_t *hd);
lst_t *add_nodeend(lst_t **hd, char *dir);
void fre_lst(lst_t *hd);

int cant_opn(char *f_path);
int proc_fle_cmd(char *f_path, int *ex_retn);
#endif /* _SHELL_H_ */
