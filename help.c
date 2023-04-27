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
 * g_pid - func to get the current process ID.
 * Description: it opens the stat file, a space-delimited file containing
 *              information about the current process. The PID is the
 *              first word in the file. The function reads the PID into
 *              a buffer and replace the space at the end with a \0 byte.
 *
 * Return: current process ID or NULL on failure.
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
 * g_env_val - Gets the value corresponding to an environmental variable.
 * @begin: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *g_env_val(char *begin, int ln)
{
	char **var_addr;
	char *replace = NULL, *tmp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_addr = _getenv(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(_strlen(temp) + 1);
		if (replacement)
			_strcpy(replacement, temp);
	}

	return (replacement);
}

/**
 * variable_replacement - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void variable_replacement(char **line, int *exe_ret)
{
	int j, k = 0, len;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
				old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				replacement = get_pid();
				k = j + 2;
			}
			else if (old_line[j + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				k = j + 2;
			}
			else if (old_line[j + 1])
			{
				/* extract the variable name to search for */
				for (k = j + 1; old_line[k] &&
						old_line[k] != '$' &&
						old_line[k] != ' '; k++)
					;
				len = k - (j + 1);
				replacement = get_env_value(&old_line[j + 1], len);
			}
			new_line = malloc(j + _strlen(replacement)
					  + _strlen(&old_line[k]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, j);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			j = -1;
		}
	}
}
