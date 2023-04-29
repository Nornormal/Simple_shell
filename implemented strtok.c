#include "shell.h"

/**
 * tok_ln - func locates the delimiter index.
 * @str: string to be searched.
 * @delim: delimiter character.
 *
 * Return: delimiter index the end of str.
 */
int tok_ln(char *str, char *delim)
{
	int idx = 0, ln = 0;

	while (*(str + idx) && *(str + idx) != *delim)
	{
		ln++;
		idx++;
	}

	return (ln);
}

/**
 * cnt_tok - func counts the number of delimited words
 * @str: string to be searched.
 * @delim: delimiter character.
 *
 * Return: number of words within str.
 */
int cnt_tok(char *str, char *delim)
{
	int idx, tok = 0, ln = 0;

	for (idx = 0; *(str + idx); idx++)
		ln++;

	for (idx = 0; idx < ln; idx++)
	{
		if (*(str + idx) != *delim)
		{
			tok++;
			idx += tok_ln(str + idx, delim);
		}
	}

	return (tok);
}

/**
 * _strtok - fun tokenize a string.
 * @lne: string.
 * @delim: delimiter char to tokenize the string by.
 *
 * Return: pointer to the tokenized words.
 */
char **_strtok(char *lne, char *delim)
{
	char **pnt;
	int idx = 0, tok, t, letter, l;

	tok = cnt_tok(lne, delim);
	if (tok == 0)
		return (NULL);

	pnt = malloc(sizeof(char *) * (tok + 2));
	if (!pnt)
		return (NULL);

	for (t = 0; t < tok; t++)
	{
		while (lne[idx] == *delim)
			idx++;

		letter = tok_ln(lne + idx, delim);

		pnt[t] = malloc(sizeof(char) * (letter + 1));
		if (!pnt[t])
		{
			for (idx -= 1; idx >= 0; idx--)
				free(pnt[idx]);
			free(pnt);
			return (NULL);
		}

		for (l = 0; l < letter; l++)
		{
			pnt[t][l] = lne[idx];
			idx++;
		}

		pnt[t][l] = '\0';
	}
	pnt[t] = NULL;
	pnt[t + 1] = NULL;

	return (pnt);
}
