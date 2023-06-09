#include "shell.h"

/**
 * hlp_env - func prints info on the 'env' command.
 */
void hlp_env(void)
{
	char *outp = "env: env\n\t Prints the current environment..\n";

	write(STDOUT_FILENO, outp, _strlen(outp));
}

/**
 * hlp_setenv - func prints info on the 'setenv' command.
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
 * hlp_unsetenv - func prints info on the 'unsetenv' command.
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
