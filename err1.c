#include "shell.h"

/**
 * err_env - func to creates an error message for shell_cmd_env errors.
 * @ag: array of arguments passed to the command.
 *
 * Return: the string error.
 */
char *err_env(char **ag)
{
	char *err, *hst_str;
	int ln;

	hst_str = _itoa(hst);
	if (!hst_str)
		return (NULL);

	ag--;
	ln = _strlen(nme) + _strlen(hst_str) + _strlen(ag[0]) + 45;
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
	_strcat(err, ": Unable to add / remove from environment\n");

	free(hst_str);
	return (err);
}

/**
 * err_1 - func to create an error message for shell_cmd_alias errors.
 * @ag: array of arguments passed to the command.
 *
 * Return: The string error.
 */
char *err_1(char **ag)
{
	char *err;
	int ln;

	ln = _strlen(nme) + _strlen(ag[0]) + 13;
	err = malloc(sizeof(char) * (ln + 1));
	if (!err)
		return (NULL);

	_strcpy(err, "alias: ");
	_strcat(err, ag[0]);
	_strcat(err, " Not Found\n");

	return (err);
}

/**
 * err_2_exit - func to create an error message for shell_cmd_exit errors.
 * @ag: array of arguments passed to the command.
 *
 * Return: The string error.
 */
char *err_2_exit(char **ag)
{
	char *err, *hst_str;
	int ln;

	hst_str = _itoa(hst);
	if (!hst_str)
		return (NULL);

	ln = _strlen(nme) + _strlen(hst_str) + _strlen(ag[0]) + 27;
	err = malloc(sizeof(char) * (ln + 1));
	if (!err)
	{
		free(hst_str);
		return (NULL);
	}

	_strcpy(err, nme);
	_strcat(err, ": ");
	_strcat(err, hst_str);
	_strcat(err, ": Exit: illegal number: ");
	_strcat(err, ag[0]);
	_strcat(err, "\n");

	free(hst_str);
	return (err);
}

/**
 * err_2_cd - func to create an error message for shell_cmd_cd errors.
 * @ag: array of arguments passed to the command.
 *
 * Return: The string error.
 */
char *err_2_cd(char **ag)
{
	char *err, *hst_str;
	int ln;

	hst_str = _itoa(hst);
	if (!hst_str)
		return (NULL);

	if (ag[0][0] == '-')
		ag[0][2] = '\0';
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
	if (ag[0][0] == '-')
		_strcat(err, ": cd: illegal option ");
	else
		_strcat(err, ": cd: can't cd to ");
	_strcat(err, ag[0]);
	_strcat(err, "\n");

	free(hst_str);
	return (err);
}

/**
 * err_2_syntax - func to create an error message for syntax errors.
 * @ag: array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *err_2_syntax(char **ag)
{
	char *err, *hst_str;
	int ln;

	hst_str = _itoa(hst);
	if (!hst_str)
		return (NULL);

	ln = _strlen(nme) + _strlen(hst_str) + _strlen(ag[0]) + 33;
	err = malloc(sizeof(char) * (ln + 1));
	if (!err)
	{
		free(hst_str);
		return (NULL);
	}

	_strcpy(err, nme);
	_strcat(err, ": ");
	_strcat(err, hst_str);
	_strcat(err, ": Syntax Error: \"");
	_strcat(err, ag[0]);
	_strcat(err, "\" Unexpected\n");

	free(hst_str);
	return (err);
}
