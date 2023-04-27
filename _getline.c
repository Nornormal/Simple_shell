#include "shell.h"

/**
 * _realloc - function that reallocate a memory block.
 * @pnt: pointer to memory that allocated.
 * @o_size: size of the allocated space of @pnt.
 * @n_size: size of the new memory.
 *
 * Return: pointer if n_size == o_size.
 *         or NULL if n_size == 0 or pnt is not NULL.
 *         or a pointer to the reallocated memory block.
 */
void *_realloc(void *pnt, unsigned int o_size, unsigned int n_size)
{
	void *memy;
	char *pnt_cp, *fill;
	unsigned int idx;

	if (n_size == o_size)
		return (pnt);

	if (pnt == NULL)
	{
		memy = malloc(n_size);
		if (memy == NULL)
			return (NULL);

		return (memy);
	}

	if (n_size == 0 && pnt != NULL)
	{
		free(pnt);
		return (NULL);
	}

	pnt_cp = pnt;
	memy = malloc(sizeof(*pnt_cp) * n_size);
	if (memy == NULL)
	{
		free(pnt);
		return (NULL);
	}
	fill = memy;

	for (idx = 0; idx < o_size && idx < n_size; idx++)
		fill[idx] = *pnt_cp++;

	free(pnt);
	return (memy);
}

/**
 * chg_lpnt - function that change line point variable for _getline.
 * @lpnt: buffer storing the input string.
 * @n: size of lpnt.
 * @buf: string to changed to @lpnt.
 * @bsize: size of buffer.
 */
void chg_lpnt(char **lpnt, size_t *n, char *buf, size_t bsize)
{
	if (*lpnt == NULL)
	{
		if (bsize > 120)
			*n = bsize;
		else
			*n = 120;
		*lpnt = buf;
	}
	else if (*n < bsize)
	{
		if (bsize > 120)
			*n = bsize;
		else
			*n = 120;
		*lpnt = buf;
	}
	else
	{
		_strcpy(*lpnt, buf);
		free(buf);
	}
}

/**
 * _getline - function that read input from a stream.
 * @lpnt: buffer storing the input string.
 * @n: size of @lpnt.
 * @r_stream: The stream read.
 *
 * Return: number of bytes read.
 */
ssize_t _getline(char **lpnt, size_t *n, FILE *r_stream)
{
	static ssize_t inpt;
	ssize_t retn;
	char ch = 'x', *buf;
	int rd;

	if (inpt == 0)
		fflush(r_stream);
	else
		return (-1);
	inpt = 0;

	buf = malloc(sizeof(char) * 120);
	if (!buf)
		return (-1);

	while (ch != '\n')
	{
		rd = read(STDIN_FILENO, &ch, 1);
		if (rd == -1 || (rd == 0 && inpt == 0))
		{
			free(buf);
			return (-1);
		}
		if (rd == 0 && inpt != 0)
		{
			inpt++;
			break;
		}

		if (inpt >= 120)
			buf = _realloc(buf, inpt, inpt + 1);

		buf[inpt] = ch;
		inpt++;
	}
	buf[inpt] = '\0';

	chg_lpnt(lpnt, n, buf, inpt);

	retn = inpt;
	if (rd != 0)
		inpt = 0;
	return (retn);
}
