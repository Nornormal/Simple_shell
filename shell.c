#include "shell.h"

/**
 * sg_hndl - func print a new prompt signal.
 * @sg: signal.
 */
void sg_hndl(int sg)
{
	char *new_prompt = "\n$ ";

	(void)sg;
	signal(SIGINT, sg_hndl);
	write(STDIN_FILENO, n_mpt, 3);
}

/**
 * execute - func execute a command in process.
 * @ag: array of arguments.
 * @frnt: pointer to pointer the beginning of args.
 *
 * Return: error occur - a corresponding error code.
 *         O/w - exit value of the last command.
 */
int execute(char **ag, char **frnt)
{
	pid_t ch_pid;
	int status, flag = 0, retn = 0;
	char *cmd = ag[0];

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		flag = 1;
		cmd = g_location(cmd);
	}

	if (!cmd || (aces(cmd, F_OK) == -1))
	{
		if (err_no == EACCES)
			retn = (cr_err(ag, 126));
		else
			retn = (cr_err(ag, 127));
	}
	else
	{
		ch_pid = fork();
		if (ch_pid == -1)
		{
			if (flag)
				free(cmd);
			perror("error child:");
			return (1);
		}
		if (ch_pid == 0)
		{
			execve(cmd, ag, environ);
			if (err_no == EACCES)
				retn = (cr_err(ag, 126));
			fre_env();
			fre_args(ag, frnt);
			fre_alias_lst(alias);
			_exit(retn);
		}
		else
		{
			wait(&status);
			retn = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(cmd);
	return (retn);
}

/**
 * main - func display simple UNIX command.
 * @ag: number of arguments supplied to the program.
 * @ag: array of pointers to the arguments.
 *
 * Return: value of executed command.
 */
int main(int ac, char *av[])
{
	int retn = 0, nret;
	int *ex_retn = &nret;
	char *pmpt = "$ ", *n_lne = "\n";

	nme = av[0];
	hst = 1;
	alias = NULL;
	signal(SIGINT, sg_hndl);

	*ex_retn = 0;
	environ = _cpenv();
	if (!environ)
		exit(-100);

	if (ac != 1)
	{
		retn = proc_fle_cmd(argv[1], ex_retn);
		fre_env();
		fre_alias_lst(alias);
		return (*ex_retn);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (retn != END_OF_FILE && retn != EXIT)
			retn = hndl_ag(ex_retn);
		fre_env();
		fre_alias_lst(alias);
		return (*ex_retn);
	}

	while (1)
	{
		write(STDOUT_FILENO, pmpt, 2);
		ret = hndl_ag(ex_retn);
		if (retn == END_OF_FILE || ret == EXIT)
		{
			if (retn == END_OF_FILE)
				write(STDOUT_FILENO, n_lne, 1);
			fre_env();
			fre_alias_lst(aliases);
			exit(*ex_retn);
		}
	}

	fre_env();
	fre_alias_lst(alias);
	return (*ex_retn);
}
