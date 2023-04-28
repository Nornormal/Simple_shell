#include "shell.h"


/**
 * _strcpy - copy the string pointed to by src.
 * @dest: a pointer to the destination string.
 * @src: a pointer to the the source string.
 *
 * Return: Pointer to dest.
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - Concantenates two strings.
 * @dest: a pointer to destination string.
 * @src: a pointer to source string.
 *
 * Return: Pointer to destination.
 */
char *_strcat(char *dest, const char *src)
{
	char *destTmp;
	const char *srcTmp;

	destTmp = dest;
	srcTmp =  src;

	while (*destTmp != '\0')
		destTmp++;

	while (*srcTmp != '\0')
		*destTmp++ = *srcTmp++;
	*destTmp = '\0';
	return (dest);
}

/**
 * _strncat - Concantenates two strings where n number
 *            of byte from source.
 * @dest: a pointer to destination string.
 * @src: a pointer to source string.
 * @n: no of byte to copy from src.
 *
 * Return: Pointer to destination string.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_ln = _strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_ln + i] = src[i];
	dest[dest_ln + i] = '\0';

	return (dest);
}

/**
 * _strlen - calcu length of a string.
 * @s: pointer to char string.
 *
 * Return: length of char string.
 */
int _strlen(const char *s)
{
	int lgth = 0;

	if (!s)
		return (lgth);
	for (lgth = 0; s[lgth]; lgth++)
		;
	return (lgth);
}
