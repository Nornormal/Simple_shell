#include "shell.h"

/**
 * _cpenv - func to create a copy of the environment.
 *
 * Return: NULL when error occurs.
 *         or O/w - pointer to pointer to the new copy.
 */
char **_cpenv(void)
{
	char **n_environ;
	size_t size;
	int idx;

	for (size = 0; environ[size]; size++)
		;

	n_environ = malloc(sizeof(char *) * (size + 1));
	if (!n_environ)
		return (NULL);

	for (idx = 0; environ[idx]; idx++)
	{
		n_environ[idx] = malloc(_strlen(environ[idx]) + 1);

		if (!n_environ[idx])
		{
			for (idx--; idx >= 0; idx--)
				free(n_environ[idx]);
			free(n_environ);
			return (NULL);
		}
		_strcpy(n_environ[idx], environ[idx]);
	}
	n_environ[idx] = NULL;

	return (n_environ);
}

/**
 * fre_env - func to free the the environment copy.
 */
void fre_env(void)
{
	int idx;

	for (idx = 0; environ[idx]; idx++)
		free(environ[idx]);
	free(environ);
}

/**
 * _getenv - func to get an env variable from the PATH.
 * @var: The name of the envl variable to get.
 *
 * Return: NULL when the env variable does not exist.
 *         or - pointer to the env variable.
 */
char **_getenv(const char *var)
{
	int idx, ln;

	ln = _strlen(var);
	for (idx = 0; environ[idx]; idx++)
	{
		if (_strncmp(var, environ[idx], ln) == 0)
			return (&environ[idx]);
	}

	return (NULL);
}
