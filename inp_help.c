#include "shell.h"

/**
 * g_ag - func gets a command input.
 * @lne: buff to store command.
 * @ex_retn: return value of the last command.
 *
 * Return: NULL : error.
 *         or pointer to stored command.
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
 * call_ag - func partitions ops from commands.
 * @ag: array of argument.
 * @frnt: pointer to pointer to the beginning of args.
 * @ex_retn: return value of last command.
 *
 * Return: @retn value of the last command.
 */
int call_ag(char **ag, char **frnt, int *ex_retn)
{
	int retn, idx;

	if (!ag[0])
		return (*ex_retn);
	for (idx = 0; ag[idx]; idx++)
	{
		if (_strncmp(ag[idx], "||", 2) == 0)
		{
			free(ag[idx]);
			ag[idx] = NULL;
			ag = rep_alias(ag);
			retn = run_ag(ag, frnt, ex_retn);
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
			ag = rep_alias(ag);
			retn = run_ag(ag, frnt, ex_retn);
			if (*ex_retn == 0)
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
	ag = rep_alias(ag);
	retn = run_ag(ag, frnt, ex_retn);
	return (retn);
}

/**
 * run_ag - func to call the execution of a command.
 * @ag: array of arguments.
 * @frnt: pointer to pointer to the beginning of args.
 * @ex_retn: @retn value of the parent process' last exec cmd.
 *
 * Return: The return value of the last executed command.
 */
int run_ag(char **ag, char **frnt, int *ex_retn)
{
	int retn, i;
	int (*builtin)(char **ag, char **frnt);

	builtin = g_builtin(ag[0]);

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
 * hndl_ag - func to get, call and run the execution of a cmd.
 * @ex_retn: @retn value of the parent process' last exec cmd.
 *
 * Return: -2 : EOF is read.
 *         -1 : input can't be tokenized.
 */
int hndl_ag(int *ex_retn)
{
	int retn = 0, idx;
	char **ag, *lne = NULL, **frnt;

	lne = g_ag(lne, ex_retn);
	if (!lne)
		return (END_OF_FILE);

	ag = _strtok(lne, " ");
	free(lne);
	if (!ag)
		return (retn);
	if (check_ag(ag) != 0)
	{
		*ex_retn = 2;
		fre_ag(ag, ag);
		return (*ex_retn);
	}
	frnt = ag;

	for (idx = 0; ag[idx]; idx++)
	{
		if (_strncmp(ag[idx], ";", 1) == 0)
		{
			free(ag[idx]);
			ag[idx] = NULL;
			retn = call_ag(ag, frnt, ex_retn);
			ag = &ag[++idx];
			idx = 0;
		}
	}
	if (ag)
		retn = call_ag(ag, frnt, ex_retn);

	free(frnt);
	return (retn);
}

/**
 * check_ag - fun check for leading ';', ';;', '&&', or '||'.
 * @ag: pntr to pntr to tokenized commands & arguments.
 *
 * Return: 2- : invalid position of ; , && , ||.
 *	   or - 0.
 */
int check_ag(char **ag)
{
	size_t i;
	char *curr, *nxt;

	for (i = 0; ag[i]; i++)
	{
		curr = ag[i];
		if (curr[0] == ';' || curr[0] == '&' || curr[0] == '|')
		{
			if (i == 0 || curr[1] == ';')
				return (cr_err(&ag[i], 2));
			nxt = ag[i + 1];
			if (nxt && (nxt[0] == ';' || nxt[0] == '&' || nxt[0] == '|'))
				return (cr_err(&ag[i + 1], 2));
		}
	}
	return (0);
}
