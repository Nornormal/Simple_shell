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
	n_lne = malloc(nw_ln + 1);
	if (!nw_lne)
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
					new_line[j++] = ' ';
				new_line[j++] = ';';
				if (next != ' ')
					new_line[j++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (next == '&' && previous != ' ')
					new_line[j++] = ' ';
				else if (previous == '&' && next != ' ')
				{
					new_line[j++] = '&';
					new_line[j++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && previous != ' ')
					new_line[j++]  = ' ';
				else if (previous == '|' && next != ' ')
				{
					new_line[j++] = '|';
					new_line[j++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (i != 0 && old_line[i - 1] != ' ')
				new_line[j++] = ' ';
			new_line[j++] = ';';
			if (next != ' ' && next != ';')
				new_line[j++] = ' ';
			continue;
		}
		new_line[j++] = old_line[i];
	}
	new_line[j] = '\0';

	free(*line);
	*line = new_line;
}

/**
 * get_new_len - Gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line: The line to check.
 *
 * Return: The new length of the line.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t get_new_len(char *line)
{
	size_t i;
	ssize_t new_len = 0;
	char current, next;

	for (i = 0; line[i]; i++)
	{
		current = line[i];
		next = line[i + 1];
		if (current == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (current == ';')
			{
				if (next == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (line[i - 1] == ';' && next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
			}
			else
				logical_ops(&line[i], &new_len);
		}
		else if (current == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				new_len++;
			if (next != ' ' && next != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}
/**
 * logical_ops - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_len: Pointer to new_len in get_new_len function.
 */
void logical_ops(char *line, ssize_t *new_len)
{
	char previous, current, next;

	previous = *(line - 1);
	current = *line;
	next = *(line + 1);

	if (current == '&')
	{
		if (next == '&' && previous != ' ')
			(*new_len)++;
		else if (previous == '&' && next != ' ')
			(*new_len)++;
	}
	else if (current == '|')
	{
		if (next == '|' && previous != ' ')
			(*new_len)++;
		else if (previous == '|' && next != ' ')
			(*new_len)++;
	}
}
