#include "shell.h"

/**
 * g_location - func locate a command PATH.
 * @cmd: command to locate.
 *
 * Return: NULL- if error occur or command cannot found.
 *         Or - pathname of the command.
 */
char *g_location(char *cmd)
{
	char **path, *tmp;
	lst_t *dirs, *hd;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = g_path_dir(*path + 5);
	hd = dirs;

	while (dirs)
	{
		tmp = malloc(_strlen(dirs->dir) + _strlen(cmd) + 2);
		if (!tmp)
			return (NULL);

		_strcpy(tmp, dirs->dir);
		_strcat(tmp, "/");
		_strcat(tmp, cmd);

		if (stat(tmp, &st) == 0)
		{
			fre_lst(hd);
			return (tmp);
		}

		dirs = dirs->nxt;
		free(temp);
	}

	fre_lst(hd);

	return (NULL);
}

/**
 * fill_path_dir - func Copy path + also replaces colons (:) with
 * 	current working directory.
 * @path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *	   with the current working directory.
 */
char *fill_path_dir(char *path)
{
	int i, lgth = 0;
	char *path_cp, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				lgth += _strlen(pwd) + 1;
			else
				lgth++;
		}
		else
			lgth++;
	}
	path_cp = malloc(sizeof(char) * (lgth + 1));
	if (!path_cp)
		return (NULL);
	path_cp[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(path_cp, pwd);
				_strcat(path_cp, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(path_cp, ":");
				_strcat(path_cp, pwd);
			}
			else
				_strcat(path_cp, ":");
		}
		else
		{
			_strncat(path_cp, &path[i], 1);
		}
	}
	return (path_cp);
}

/**
 * g_path_dir - func tokenize a colon-separates list of directories
 * @path: The colon-separated list of directories.
 *
 * Return: pointer to the first linked list.
 */
lst_t *g_path_dir(char *path)
{
	int idx;
	char **dirs, *path_cp;
	lst_t *hd = NULL;

	path_cp = fill_path_dir(path);
	if (!path_cp)
		return (NULL);
	dirs = _strtok(path_cp, ":");
	free(path_cp);
	if (!dirs)
		return (NULL);

	for (i = 0; dirs[idx]; idx++)
	{
		if (add_nodeend(&hd, dirs[idx]) == NULL)
		{
			fre_lst(hd);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (hd);
}
