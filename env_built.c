#include "shell.h"

/**
 * shell_cmd_env - func print the current environment.
 * @ag: array of arguments passed to shell.
 * @frnt: pointer to pointer to beginning of args.
 *
 * Return: -1 when error occurs.
 *	   or - 0.
 *
 * Description: to print one variable only per line in the
 *              format 'variable'='value'.
 */
int shell_cmd_env(char **ag, char __attribute__((__unused__)) **frnt)
{
	int idx;
	char nch = '\n';

	if (!environ)
		return (-1);

	for (idx = 0; environ[idx]; idx++)
	{
		write(STDOUT_FILENO, environ[idx], _strlen(environ[idx]));
		write(STDOUT_FILENO, &nch, 1);
	}

	(void)ag;
	return (0);
}

/**
 * shell_cmd_setenv - func to change or add an envir. variable to the PATH.
 * @ag: array of arguments passed to the shell.
 * @frnt: pointer to pointer to beginning of args.
 * Description: ag[1] name of the new or existing PATH variable.
 *              ag[2] value to set the new or changed variable to.
 *
 * Return: -1 when error occurs.
 *         or - 0.
 */
int shell_cmd_setenv(char **ag, char __attribute__((__unused__)) **frnt)
{
	char **env_var = NULL, **n_environ, *n_val;
	size_t size;
	int idx;

	if (!ag[0] || !ag[1])
		return (cr_err(ag, -1));

	n_val = malloc(_strlen(ag[0]) + 1 + _strlen(ag[1]) + 1);
	if (!n_val)
		return (cr_err(ag, -1));
	_strcpy(n_val, ag[0]);
	_strcat(n_val, "=");
	_strcat(n_val, ag[1]);

	env_var = _getenv(ag[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = n_val;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	n_environ = malloc(sizeof(char *) * (size + 2));
	if (!n_environ)
	{
		free(n_val);
		return (cr_err(ag, -1));
	}

	for (idx = 0; environ[idx]; idx++)
		n_environ[idx] = environ[idx];

	free(environ);
	environ = n_environ;
	environ[idx] = n_val;
	environ[idx + 1] = NULL;

	return (0);
}

/**
 * shell_cmd_unsetenv - func to delete an env. variable from the PATH.
 * @ag: array of arguments passed to the shell.
 * @frnt: pointer to pointer to  beginning of args.
 * Description: ag[1] is the PATH variable to remove.
 *
 * Return: -1 when error occurs.
 *         or - 0.
 */
int shell_cmd_unsetenv(char **ag, char __attribute__((__unused__)) **frnt)
{
	char **env_var, **n_environ;
	size_t size;
	int idx, idx2;

	if (!ag[0])
		return (cr_err(ag, -1));
	env_var = _getenv(ag[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	n_environ = malloc(sizeof(char *) * size);
	if (!n_environ)
		return (cr_err(ag, -1));

	for (idx = 0, idx2 = 0; environ[idx]; idx++)
	{
		if (*env_var == environ[idx])
		{
			free(*env_var);
			continue;
		}
		n_environ[idx2] = environ[idx];
		idx2++;
	}
	free(environ);
	environ = n_environ;
	environ[size - 1] = NULL;

	return (0);
}
