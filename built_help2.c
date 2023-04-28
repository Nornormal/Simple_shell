#include "shell.h"

void hlp_env(void);
void hlp_setenv(void);
void hlp_unsetenv(void);
void hlp_history(void);

/**
 * hlp_env - function prints information on the built-in shell_cmd command 'env'.
 */
void hlp_env(void)
{
	char *outp = "env: env\n\t Prints the current environment..\n";

	write(STDOUT_FILENO, outp, _strlen(outp));
}

/**
 * hlp_setenv - function prints information on the built-in shell_cmd command 'setenv'.
 */
void hlp_setenv(void)
{
	char *outp = "setenv: setenv [VARIABLE] [VALUE]\n\t Initializes a new";

	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = "environment variable, or modifies an existing one..\n\n";
	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = "\t Upon failure, prints a message to stderr..\n";
	write(STDOUT_FILENO, outp, _strlen(outp));
}

/**
 * hlp_unsetenv - function prints information on the built-in shell_cmd command
 * 'unsetenv'..
 */
void hlp_unsetenv(void)
{
	char *outp = "unsetenv: unsetenv [VARIABLE]\n\t Removes an ";

	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = "environmental variable..\n\n\t Upon failure, prints a ";
	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = "message to stderr..\n";
	write(STDOUT_FILENO, outp, _strlen(outp));
}
