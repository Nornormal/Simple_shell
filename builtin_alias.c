#include "shell.h"

/**
 * shell_cmd_alias - is a built-in command that prints either all alias, specific
 * alias, or sets an alias.
 * @ag: array of arguments.
 * @frnt: pointer to pointer to the beginning of args.
 *
 * Return: -1 when error occurs.
 *         or - 0.
 */
int shell_cmd_alias(char **ag, char __attribute__((__unused__)) **frnt)
{
	alias_t *tmp = alias;
	int i, retn = 0;
	char *val;

	if (!ag[0])
	{
		while (tmp)
		{
			pr_alias(tmp);
			tmp = tmp->nxt;
		}
		return (retn);
	}
	for (i = 0; ag[i]; i++)
	{
		tmp = alias;
		val = _strchr(ag[i], '=');
		if (!val)
		{
			while (tmp)
			{
				if (_strcmp(ag[i], tmp->nme) == 0)
				{
					pr_alias(tmp);
					break;
				}
				tmp = tmp->nxt;
			}
			if (!tmp)
				retn = cr_err(ag + i, 1);
		}
		else
			st_alias(ag[i], val);
	}
	return (retn);
}

/**
 * st_alias - function that either set an existing alias 'name' with new value,
 * 'value' or creates new alias with 'name' and 'value'.
 * @var_nme: alias name.
 * @val: alias value. First character is a '='.
 */
void st_alias(char *var_nme, char *val)
{
	alias_t *tmp = alias;
	int ln, a, b;
	char *n_val;

	*val = '\0';
	val++;
	ln = _strlen(val) - _strspn(val, "'\"");
	n_val = malloc(sizeof(char) * (ln + 1));
	if (!n_val)
		return;
	for (a = 0, b = 0; val[a]; a++)
	{
		if (val[a] != '\'' && val[a] != '"')
			n_val[b++] = val[a];
	}
	n_val[b] = '\0';
	while (tmp)
	{
		if (_strcmp(var_nme, tmp->nme) == 0)
		{
			free(tmp->val);
			tmp->val = n_val;
			break;
		}
		tmp = tmp->nxt;
	}
	if (!tmp)
		add_aliasend(&alias, var_nme, n_val);
}

/**
 * pr_alias - function that print the alias in the format name='value'.
 * @alias: Pointer to alias.
 */
void pr_alias(alias_t *alias)
{
	char *alias_str;
	int ln = _strlen(alias->nme) + _strlen(alias->val) + 4;

	alias_str = malloc(sizeof(char) * (ln + 1));
	if (!alias_str)
		return;
	_strcpy(alias_str, alias->nme);
	_strcat(alias_str, "='");
	_strcat(alias_str, alias->val);
	_strcat(alias_str, "'\n");

	write(STDOUT_FILENO, alias_str, ln);
	free(alias_str);
}
/**
 * rep_alias - func that goes through the arguments and replace any matching alias
 * with their value.
 * @ag: pointer to pointer to the arguments.
 *
 * Return: pointer to pointer to the arguments.
 */
char **rep_alias(char **ag)
{
	alias_t *tmp;
	int i;
	char *n_val;

	if (_strcmp(ag[0], "alias") == 0)
		return (ag);
	for (i = 0; ag[i]; i++)
	{
		tmp = alias;
		while (tmp)
		{
			if (_strcmp(ag[i], tmp->nme) == 0)
			{
				n_val = malloc(sizeof(char) * (_strlen(tmp->val) + 1));
				if (!n_val)
				{
					fre_ag(ag, ag);
					return (NULL);
				}
				_strcpy(n_val, tmp->val);
				free(ag[i]);
				ag[i] = n_val;
				i--;
				break;
			}
			tmp = tmp->nxt;
		}
	}

	return (ag);
}

