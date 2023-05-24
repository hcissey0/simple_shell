#include "shell.h"

/**
 * _strlen - finds the length of a string
 * @s: the string
 *
 * Return: the length of the string
 */
int _strlen(char *s)
{
	int len, i;

	for (i = 0; s[i] != '\0'; i++)
		len++;
	return (len);
}

/**
 * _strcpy - copies a string into another string
 * @dest: the destination of the string
 * @src: the source to copy the string from
 *
 * Return: a pointer to the destination
 */
char *_strcpy(char *dest, char *src)
{
	int i, n = 0;

	while (src[n] != '\0')
		n++;
	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - adds (concatenates) two strings
 * @dest: destination of the concatenaton
 * @src: source of the concatenation
 *
 * Return: pointer the destination
 */
char *_strcat(char *dest, char *src)
{
	int n = 0, i;

	while (dest[n] != '\0')
		n++;
	for (i = 0; src[i] != '\0'; i++)
		dest[n + i] = src[i];
	dest[n + i] = '\0';
	return (dest);
}

/**
 * _strncat - concatenates two strings to a number of chars
 * @dest: the destination
 * @src: the source
 * @n: the limit
 *
 * Return: pointer to the destination
 */
char *_strncat(char *dest, char *src, int n)
{
	int i = 0, j;

	while (dest[i] != '\0')
		i++;
	for (j = 0; j < n && src[j] != '\0'; j++)
		dest[i + j] = src[j];
	dest[i + j] = '\0';
	return (dest);
}

/**
 * _strncpy - copies a string to a string
 * @dest: the destination
 * @src: the source
 * @n: the limit or size
 *
 * Return: a pointer to the destination
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	for (; i < n; i++)
		dest[i] = '\0';
	return (dest);
}
