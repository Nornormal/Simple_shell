#include "shell.h"

/**
 * hndl_lne - func to partitions a line read from a standard input as needed.
 * @lne: pointer to a line read from standard input.
 * @rread: length of line.
 *
 * Description: the spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void hndl_lne(char **lne, ssize_t rread)
{
	char *o_lne, *n_lne;
	char prev, curr, nxt;
	size_t i, j;
	ssize_t n_ln;

	n_ln = g_n_ln(*lne);
	if (n_ln == rread - 1)
		return;
	n_lne = malloc(n_ln + 1);
	if (!n_lne)
		return;
	j = 0;
	o_lne = *lne;
	for (i = 0; o_lne[i]; i++)
	{
		curr = o_lne[i];
		nxt = o_lne[i + 1];
		if (i != 0)
		{
			prev = o_lne[i - 1];
			if (curr == ';')
			{
				if (nxt == ';' && prev != ' ' && prev != ';')
				{
					n_lne[j++] = ' ';
					n_lne[j++] = ';';
					continue;
				}
				else if (prev == ';' && nxt != ' ')
				{
					n_lne[j++] = ';';
					n_lne[j++] = ' ';
					continue;
				}
				if (prev != ' ')
					n_lne[j++] = ' ';
				n_lne[j++] = ';';
				if (nxt != ' ')
					n_lne[j++] = ' ';
				continue;
			}
			else if (curr == '&')
			{
				if (nxt == '&' && prev != ' ')
					n_lne[j++] = ' ';
				else if (prev == '&' && nxt != ' ')
				{
					n_lne[j++] = '&';
					n_lne[j++] = ' ';
					continue;
				}
			}
			else if (curr == '|')
			{
				if (nxt == '|' && prev != ' ')
					n_lne[j++]  = ' ';
				else if (prev == '|' && nxt != ' ')
				{
					n_lne[j++] = '|';
					n_lne[j++] = ' ';
					continue;
				}
			}
		}
		else if (curr == ';')
		{
			if (i != 0 && o_lne[i - 1] != ' ')
				n_lne[j++] = ' ';
			n_lne[j++] = ';';
			if (nxt != ' ' && nxt != ';')
				n_lne[j++] = ' ';
			continue;
		}
		n_lne[j++] = o_lne[i];
	}
	n_lne[j] = '\0';

	free(*lne);
	*lne = n_lne;
}

/**
 * g_n_ln - func to get new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @lne: line to be checked.
 *
 * Return: new length of the line.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t g_n_ln(char *lne)
{
	size_t i;
	ssize_t n_ln = 0;
	char curr, nxt;

	for (i = 0; lne[i]; i++)
	{
		curr = lne[i];
		nxt = lne[i + 1];
		if (curr == '#')
		{
			if (i == 0 || lne[i - 1] == ' ')
			{
				lne[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (curr == ';')
			{
				if (nxt == ';' && lne[i - 1] != ' ' && lne[i - 1] != ';')
				{
					n_ln += 2;
					continue;
				}
				else if (lne[i - 1] == ';' && nxt != ' ')
				{
					n_ln += 2;
					continue;
				}
				if (lne[i - 1] != ' ')
					n_ln++;
				if (nxt != ' ')
					n_ln++;
			}
			else
				logic_op(&lne[i], &n_ln);
		}
		else if (curr == ';')
		{
			if (i != 0 && lne[i - 1] != ' ')
				n_ln++;
			if (nxt != ' ' && nxt != ';')
				n_ln++;
		}
		n_ln++;
	}
	return (n_ln);
}
/**
 * logic_op - func to check a line for logical operators "||" or "&&".
 * @lne: pointer to the character to be checked in the line.
 * @n_ln: Pointer to new_len in @g_n_ln function.
 */
void logic_op(char *lne, ssize_t *n_ln)
{
	char prev, curr, nxt;

	prev = *(lne - 1);
	curr = *lne;
	nxt = *(lne + 1);

	if (curr == '&')
	{
		if (nxt == '&' && prev != ' ')
			(*n_ln)++;
		else if (prev == '&' && nxt != ' ')
			(*n_ln)++;
	}
	else if (curr == '|')
	{
		if (nxt == '|' && prev != ' ')
			(*n_ln)++;
		else if (prev == '|' && nxt != ' ')
			(*n_ln)++;
	}
}
