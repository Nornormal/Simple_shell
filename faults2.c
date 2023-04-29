#include "shell.h"

/**
 * err_126 - func to create an error message for permission denied failures.
 * @ag: An array of arguments passed to the command.
 *
 * Return: The string error.
 */
char *err_126(char **ag)
{
	char *err, *hst_str;
	int ln;

	hst_str = _itoa(hst);
	if (!hst_str)
		return (NULL);

	ln = _strlen(nme) + _strlen(hst_str) + _strlen(ag[0]) + 24;
	err = malloc(sizeof(char) * (ln + 1));
	if (!err)
	{
		free(hst_str);
		return (NULL);
	}

	_strcpy(err, nme);
	_strcat(err, ": ");
	_strcat(err, hst_str);
	_strcat(err, ": ");
	_strcat(err, ag[0]);
	_strcat(err, ": Permission Denied\n");

	free(hst_str);
	return (err);
}

/**
 * err_127 - func to create an error message for command not found failures.
 * @ag: array of arguments passed to the command.
 *
 * Return: The string error.
 */
char *err_127(char **ag)
{
	char *err, *hst_str;
	int ln;

	hst_str = _itoa(hst);
	if (!hst_str)
		return (NULL);

	ln = _strlen(nme) + _strlen(hst_str) + _strlen(ag[0]) + 16;
	err = malloc(sizeof(char) * (ln + 1));
	if (!err)
	{
		free(hst_str);
		return (NULL);
	}

	_strcpy(err, nme);
	_strcat(err, ": ");
	_strcat(err, hst_str);
	_strcat(err, ": ");
	_strcat(err, ag[0]);
	_strcat(err, ": Not Found\n");

	free(hst_str);
	return (err);
}
