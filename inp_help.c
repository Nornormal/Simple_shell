#include "shell.h"

/**
 * g_ag - func gets a command input.
 * @lne: buff to store command.
 * @ex_retn: return value of the last command.
 *
 * Return: NULL - If an error occur.
 *         or - a pointer to stored command.
 */
char *g_ag(char *lne, int *ex_retn)
{
	size_t n = 0;
	ssize_t read;
	char *pmpt = "$ ";

	if (lne)
		free(lne);

	read = _getline(&lne, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hst++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, pmpt, 2);
		return (g_ag(lne, ex_retn));
	}

	lne[read - 1] = '\0';
	var_replace(&lne, ex_retn);
	hndl_lne(&lne, read);

	return (lne);
}

/**
 * call_ag - func partitions operators from commands.
 * @ag: array of argument.
 * @frnt: a pointer to pointer to the beginning of args.
 * @ex_retn: return value of last command.
 *
 * Return: return value of the last command.
 */
int call_ag(char **ag, char **frnt, int *ex_retn)
{
	int retn, idx;

	if (!ag[0])
		return (*ex_retn);
	for (idx = 0; args[idx]; idx++)
	{
		if (_strncmp(ag[idx], "||", 2) == 0)
		{
			free(ag[idx]);
			ag[idx] = NULL;
			ag = replace_alias(ag);
			ret = run_ag(ag, frnt, ex_retn);
			if (*ex_retn != 0)
			{
				ag = &ag[++idx];
				idx = 0;
			}
			else
			{
				for (idx++; ag[idx]; idx++)
					free(ag[idx]);
				return (retn);
			}
		}
		else if (_strncmp(ag[idx], "&&", 2) == 0)
		{
			free(ag[idx]);
			ag[idx] = NULL;
			ag = replace_alias(ag);
			retn = run_ag(ag, frnt, ex_retn);
			if (*exe_ret == 0)
			{
				ag = &ag[++idx];
				idx = 0;
			}
			else
			{
				for (idx++; ag[idx]; idx++)
					free(ag[idx]);
				return (retn);
			}
		}
	}
	ag = replace_alias(ag);
	retn = run_ag(ag, frnt, ex_retn);
	return (retn);
}

/**
 * run_ag - func to call the execution of a command.
 * @ag: array of arguments.
 * @frnt: pointer to pointer to the beginning of args.
 * @ex_retn: return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int run_ag(char **ag, char **frnt, int *ex_retn)
{
	int retn, i;
	int (*builtin)(char **ag, char **frnt);

	builtin = get_builtin(ag[0]);

	if (builtin)
	{
		retn = builtin(ag + 1, frnt);
		if (retn != EXIT)
			*ex_retn = retn;
	}
	else
	{
		*ex_retn = execute(ag, frnt);
		retn = *ex_retn;
	}

	hst++;

	for (i = 0; ag[i]; i++)
		free(ag[i]);

	return (retn);
}

/**
 * handle_args - Gets, calls, and runs the execution of a command.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int handle_args(int *exe_ret)
{
	int ret = 0, index;
	char **args, *line = NULL, **front;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}

/**
 * check_args - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int check_args(char **args)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; args[i]; i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (create_error(&args[i], 2));
			nex = args[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_error(&args[i + 1], 2));
		}
	}
	return (0);
}
