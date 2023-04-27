#include "shell.h"

/**
 * nmb_ln - func to ount the digit length of a number.
 * @nmb: number to measure.
 *
 * Return: length of the digit.
 */
int nmb_ln(int nmb)
{
	unsigned int nmb1;
	int ln = 1;

	if (nmb < 0)
	{
		ln++;
		nmb1 = nmb * -1;
	}
	else
	{
		nmb1 = nmb;
	}
	while (nmb1 > 9)
	{
		ln++;
		nmb1 /= 10;
	}

	return (ln);
}

/**
 * _itoa - func to convert integer to a string.
 * @nmb: input integer.
 *
 * Return: converted string.
 */
char *_itoa(int nmb)
{
	char *bufr;
	int ln = nmb_ln(nmb);
	unsigned int nmb1;

	buf = malloc(sizeof(char) * (ln + 1));
	if (!buf)
		return (NULL);

	buf[ln] = '\0';

	if (nmb < 0)
	{
		nmb1 = nmb * -1;
		buf[0] = '-';
	}
	else
	{
		nmb1 = nmb;
	}

	ln--;
	do {
		buf[ln] = (nmb1 % 10) + '0';
		nmb1 /= 10;
		ln--;
	} while (nmb1 > 0);

	return (buf);
}


/**
 * cr_err - func to write a custom error message to stderr.
 * @ag: array of arguments.
 * @n_err: error value.
 *
 * Return: error value.
 */
int cr_err(char **ag, int n_err)
{
	char *err;

	switch (n_err)
	{
	case -1:
		err = err_env(ag);
		break;
	case 1:
		err = err_1(ag);
		break;
	case 2:
		if (*(ag[0]) == 'e')
			err = err_2_exit(++ag);
		else if (ag[0][0] == ';' || ag[0][0] == '&' || ag[0][0] == '|')
			err = err_2_syntax(ag);
		else
			err = err_2_cd(ag);
		break;
	case 126:
		err = err_126(ag);
		break;
	case 127:
		err = err_127(ag);
		break;
	}
	write(STDERR_FILENO, err, _strlen(err));

	if (err)
		free(err);
	return (n_err);

}
