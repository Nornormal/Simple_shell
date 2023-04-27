#include "shell.h"

/**
 * g_builtin - function that matches a command with a corresponding
 *               shell_cmd built-in function.
 * @command: command to match.
 *
 * Return: function pointer to the built-in corresponding.
 */
int (*g_builtin(char *cmd))(char **ag, char **frnt)
{
	builtin_t func[] = {
		{ "exit", shell_cmd_exit },
		{ "env", shell_cmd_env },
		{ "setenv", shell_cmd_setenv },
		{ "unsetenv", shell_cmd_unsetenv },
		{ "cd", shell_cmd_cd },
		{ "alias", shell_cmd_alias },
		{ "help", shell_cmd_hlp },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; func[i].name; i++)
	{
		if (_strcmp(func[i].name, cmd) == 0)
			break;
	}
	return (func[i].f);
}

/**
 * shell_cmd_exit - function that cause normal process termination
 *                for the shell_cmd shell.
 * @ag: array of arguments contain the exit value.
 * @frnt: pointer to pointer to the beginning of ag.
 *
 * Return: -3 when there are no arguments.
 *         or -2 for invalid given exit value.
 *         or O/w if exits with the given status val.
 *
 * Description: when returning -3, program exits back to main function.
 */
int shell_cmd_exit(char **ag, char **frnt)
{
	int i, ln_int = 10;
	unsigned int nmb = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (ag[0])
	{
		if (ag[0][0] == '+')
		{
			i = 1;
			ln_int++;
		}
		for (; ag[0][i]; i++)
		{
			if (i <= ln_int && ag[0][i] >= '0' && ag[0][i] <= '9')
				nmb = (nmb * 10) + (ag[0][i] - '0');
			else
				return (cr_error(--ag, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (nmb > max - 1)
		return (cr_error(--ag, 2));
	ag -= 1;
	fre_ag(ag, frnt);
	fre_env();
	fre_alias_lst(aliases);
	exit(nmb);
}

/**
 * shell_cmd_cd - function that change the current directory of the shell_cmd process.
 * @ag: array of arguments.
 * @frnt: pointer to pointer to the beginning of args.
 *
 * Return: -2 when the string is not a directory.
 *         -1 when an error occurs.
 *         else - 0.
 */
int shell_cmd_cd(char **ag, char __attribute__((__unused__)) **frnt)
{
	char **dir_inf, *n_lne = "\n";
	char *o_pwd = NULL, *pwd = NULL;
	struct stat dir;

	o_pwd = g_cwd(o_pwd, 0);
	if (!o_pwd)
		return (-1);

	if (ag[0])
	{
		if (*(ag[0]) == '-' || _strcmp(ag[0], "--") == 0)
		{
			if ((ag[0][1] == '-' && ag[0][2] == '\0') ||
					ag[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(ch_dir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(o_pwd);
				return (cr_error(ag, 2));
			}
		}
		else
		{
			if (stat(ag[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				ch_dir(ag[0]);
			else
			{
				free(o_pwd);
				return (cr_error(ag, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			ch_dir(*(_getenv("HOME")) + 5);
	}

	pwd = g_cwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_inf = malloc(sizeof(char *) * 2);
	if (!dir_inf)
		return (-1);

	dir_inf[0] = "OLDPWD";
	dir_inf[1] = o_pwd;
	if (shell_cmd_setenv(dir_inf, dir_inf) == -1)
		return (-1);

	dir_inf[0] = "PWD";
	dir_inf[1] = pwd;
	if (shell_cmd_setenv(dir_inf, dir_inf) == -1)
		return (-1);
	if (ag[0] && ag[0][0] == '-' && ag[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, n_lne, 1);
	}
	free(o_pwd);
	free(pwd);
	free(dir_inf);
	return (0);
}

/**
 * shell_cmd_hlp - function prints information about built-in shell_cmd commands.
 * @ag: array of arguments.
 * @frnt: pointer to the beginning of args.
 *
 * Return: -1 when error occurs.
 *         or - 0.
 */
int shell_cmd_hlp(char **ag, char __attribute__((__unused__)) **frnt)
{
	if (!ag[0])
		hlp_all();
	else if (_strcmp(ag[0], "alias") == 0)
		hlp_alias();
	else if (_strcmp(ag[0], "cd") == 0)
		hlp_cd();
	else if (_strcmp(ag[0], "exit") == 0)
		hlp_exit();
	else if (_strcmp(ag[0], "env") == 0)
		hlp_env();
	else if (_strcmp(ag[0], "setenv") == 0)
		hlp_setenv();
	else if (_strcmp(ag[0], "unsetenv") == 0)
		hlp_unsetenv();
	else if (_strcmp(ag[0], "help") == 0)
		hlp_help();
	else
		write(STDERR_FILENO, nme, _strlen(nme));

	return (0);
}
