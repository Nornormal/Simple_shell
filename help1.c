#include "shell.h"

/**
 * fre_ag - func to free up memory.
 * @ag: null-terminated pointer to  pointer containing commands/arguments.
 * @frnt: pointer to pointer to the beginning of args.
 */
void fre_ag(char **ag, char **frnt)
{
	size_t i;

	for (i = 0; ag[i] || ag[i + 1]; i++)
		free(ag[i]);

	free(frnt);
}

/**
 * g_pid - func to get the PID.
 *
 * Return: PID or NULL on failure.
 */
char *g_pid(void)
{
	size_t i = 0;
	char *buf;
	ssize_t fle;

	fle = open("/proc/self/stat", O_RDONLY);
	if (fle == -1)
	{
		perror("Cant Read File");
		return (NULL);
	}
	buf = malloc(120);
	if (!buf)
	{
		close(fle);
		return (NULL);
	}
	read(fle, buf, 120);
	while (buf[i] != ' ')
		i++;
	buf[i] = '\0';

	close(fle);
	return (buf);
}

/**
 * g_env_val - gets value of env variable.
 * @begin: env variable to search for.
 * @ln: length of env variable.
 *
 * Return: empty string : variable is not found.
 *         or - value of the env variable.
 *
 * Description: Variables were stored in the format VARIABLE=VALUE.
 */
char *g_env_val(char *begin, int ln)
{
	char **var_addr;
	char *replace = NULL, *tmp, *var;

	var = malloc(ln + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, begin, ln);

	var_addr = _getenv(var);
	free(var);
	if (var_addr)
	{
		tmp = *var_addr;
		while (*tmp != '=')
			tmp++;
		tmp++;
		replace = malloc(_strlen(tmp) + 1);
		if (replace)
			_strcpy(replace, tmp);
	}

	return (replace);
}

/**
 * var_replace - it handles variable replacement.
 * @lne: pointer to pointer containing command and arguments.
 * @ex_retn: pointer to the return value of last executed command.
 *
 * Description: Replaces $$ with the current Porcess ID, $? with the return value
 *              of the last executed program, and envr variables
 *              preceded by $ with their corresponding value.
 */
void var_replace(char **lne, int *ex_retn)
{
	int a, b = 0, ln;
	char *replace = NULL, *o_lne = NULL, *n_lne;

	o_lne = *lne;
	for (a = 0; o_lne[a]; a++)
	{
		if (o_lne[a] == '$' && o_lne[a + 1] &&
				o_lne[a + 1] != ' ')
		{
			if (o_lne[a + 1] == '$')
			{
				replace = g_pid();
				b = a + 2;
			}
			else if (o_lne[a + 1] == '?')
			{
				replace = _itoa(*ex_retn);
				b = a + 2;
			}
			else if (o_lne[a + 1])
			{
				for (b = a + 1; o_lne[b] &&
						o_lne[b] != '$' &&
						o_lne[b] != ' '; b++)
					;
				ln = b - (a + 1);
				replace = g_env_val(&o_lne[a + 1], ln);
			}
			n_lne = malloc(a + _strlen(replace)
					  + _strlen(&o_lne[b]) + 1);
			if (!lne)
				return;
			n_lne[0] = '\0';
			_strncat(n_lne, o_lne, a);
			if (replace)
			{
				_strcat(n_lne, replace);
				free(replace);
				replace = NULL;
			}
			_strcat(n_lne, &o_lne[b]);
			free(o_lne);
			*lne = n_lne;
			o_lne = n_lne;
			a = -1;
		}
	}
}
