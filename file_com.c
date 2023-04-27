#include "shell.h"

/**
 * cant_opn - func to print a "cant open" error, if
 * the file doesn't exist or lacks proper permissions.
 * @f_path: Path to the supposed file.
 *
 * Return: 127.
 */

int cant_opn(char *f_path)
{
	char *err, *hst_str;
	int ln;

	hst_str = _itoa(hst);
	if (!hst_str)
		return (127);

	ln = _strlen(nme) + _strlen(hst_str) + _strlen(f_path) + 16;
	err = malloc(sizeof(char) * (ln + 1));
	if (!err)
	{
		free(hst_str);
		return (127);
	}

	_strcpy(err, nme);
	_strcat(err, ": ");
	_strcat(err, hst_str);
	_strcat(err, ": Can't Open ");
	_strcat(err, f_path);
	_strcat(err, "\n");

	free(hst_str);
	write(STDERR_FILENO, err, ln);
	free(err);
	return (127);
}

/**
 * proc_fle_cmd - func to take a file and attempt to run the commands stored
 * within.
 * @f_path: Path to the file.
 * @ex_retn: the return value of the last executed command.
 *
 * Return: 127 when file couldn't be opened.
 *	   or -1 when malloc fails.
 *	   or the return value of the last command ran.
 */
int proc_fle_cmd(char *f_path, int *ex_retn)
{
	ssize_t fle, b_read, i;
	unsigned int lne_size = 0;
	unsigned int o_size = 120;
	char *lne, **ag, **frnt;
	char buf[120];
	int retn;

	hst = 0;
	fle = open(f_path, O_RDONLY);
	if (fle == -1)
	{
		*ex_retn = cant_opn(f_path);
		return (*ex_retn);
	}
	lne = malloc(sizeof(char) * o_size);
	if (!lne)
		return (-1);
	do {
		b_read = read(fle, buf, 119);
		if (b_read == 0 && lne_size == 0)
			return (*ex_retn);
		buf[b_read] = '\0';
		lne_size += b_read;
		lne = _realloc(lne, o_size, lne_size);
		_strcat(lne, buf);
		o_size = lne_size;
	} while (b_read);
	for (i = 0; lne[i] == '\n'; i++)
		lne[i] = ' ';
	for (; i < lne_size; i++)
	{
		if (lne[i] == '\n')
		{
			lne[i] = ';';
			for (i += 1; i < lne_size && lne[i] == '\n'; i++)
				lne[i] = ' ';
		}
	}
	var_replace(&lne, ex_retn);
	hndl_lne(&lne, lne_size);
	ag = _strtok(lne, " ");
	free(lne);
	if (!ag)
		return (0);
	if (check_ag(ag) != 0)
	{
		*ex_retn = 2;
		fre_ag(ag, ag);
		return (*ex_retn);
	}
	frnt = ag;

	for (i = 0; ag[i]; i++)
	{
		if (_strncmp(ag[i], ";", 1) == 0)
		{
			free(ag[i]);
			ag[i] = NULL;
			retn = call_ag(ag, frnt, ex_retn);
			ag = &ag[++i];
			i = 0;
		}
	}

	retn = call_ag(ag, frnt, ex_retn);

	free(frnt);
	return (retn);
}
