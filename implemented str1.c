#include "shell.h"

/**
 * _strchr - func to find a character in a string.
 * @s: string to be searche.
 * @c: character to be locate.
 *
 * Return: a pointer or NULL
 */
char *_strchr(char *s, char c)
{
	int idx;

	for (idx = 0; s[idx]; idx++)
	{
		if (s[idx] == c)
			return (s + idx);
	}

	return (NULL);
}


/**
 * _strcmp - func compare two string.
 * @s1: first string to compare.
 * @s2: second string to compare.
 *
 * Return: +ve byte or 0 or -ve byte.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
 * _strncmp - compare two strings.
 * @s1: a pointer to a string.
 * @s2: a pointer to a string.
 * @n: first n byte of the string to compare.
 *
 * Return: less 0 or 0 or greater than 0
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}

/**
 * _strspn - func calc the len of a prev substring.
 * @s: string to be search.
 * @acpt: prev to be measure.
 *
 * Return: number of bytes in s.
 */
int _strspn(char *s, char *acpt)
{
	int byte = 0;
	int idx;

	while (*s)
	{
		for (idx = 0; acpt[idx]; idx++)
		{
			if (*s == acpt[idx])
			{
				byte++;
				break;
			}
		}
		s++;
	}
	return (byte);
}
