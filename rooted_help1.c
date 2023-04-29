#include "shell.h"

/**
 * hlp_all - func prints all possible built-in shell_cmd commands.
 */
void hlp_all(void)
{
	char *outp;

	outp = "Shell_cmd\nThese shell commands are defined internally..\n";
	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = "Read more about the function 'name'..\n\n  alias   \t";
	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = "Write 'help' to see this list..\nWrite 'help name' to find ";
	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = "alias [NAME[='VALUE'] .....]\n  cd   \tcd   ";
	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = "[DIRECTORY]\n  exit  \texit [STATUS]\n  env   \tenv";
	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, outp, _strlen(outp));
}

/**
 * hlp_alias - func prints info on the command 'alias'.
 */
void hlp_alias(void)
{
	char *outp = "alias: alias [NAME[='VALUE'] ....]\n\tHandles aliases..\n";

	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = "\n\talias: Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = "the format NAME='VALUE'..\n\talias name [name2 ....]:prints";
	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = " the aliases name, name2, etc.. one per line, in the ";
	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = "form NAME='VALUE'.\n\talias NAME='VALUE' [....]: Defines";
	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = " an alias for each NAME whose VALUE is given.. If NAME ";
	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = "this already an alias, replace its value with VALUE..\n";
	write(STDOUT_FILENO, outp, _strlen(outp));
}

/**
 * hlp_cd - function prints information on the built-in shell_cmd command 'cd'.
 */
void hlp_cd(void)
{
	char *outp = "cd: cd [DIRECTORY]\n\tChanges current directory of the";

	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = " process to DIRECTORY..\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = "command is interpreted as cd $HOME.. If the argument '-' is";
	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = " given, the command is interpreted as cd $OLDPWD..\n\n";
	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = "after a change of directory..\n";
	write(STDOUT_FILENO, outp, _strlen(outp));
}

/**
 * hlp_exit - func prints info on the command 'exit'.
 */
void hlp_exit(void)
{
	char *outp = "exit: exit [STATUS]\n\tExits the shell..\n\n\tThe ";

	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = "STATUS argument is the integer used to exit the shell..";
	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = " exit 0..\n";
	write(STDOUT_FILENO, outp, _strlen(outp));
}

/**
 * hlp_help - func prints info on the command 'help'.
 */
void hlp_help(void)
{
	char *outp = "help: help\n\tSee all possible built-in shell_cmd commands..\n";

	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = "\n   help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, outp, _strlen(outp));
	outp = "built-in command..\n";
	write(STDOUT_FILENO, outp, _strlen(outp));
}
