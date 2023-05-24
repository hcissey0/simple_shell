#include "shell.h"

/**
 * _strcmp - compare two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: difference between the unmatching characters
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

/**
 * _strncmp - compare two strings
 * @s1: first string
 * @s2: second string
 * @n: the limit
 *
 * Return: difference between the last characters
 */
int _strncmp(char *s1, char *s2, int n)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0' && i < n && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

/**
 * _strchr - find first occurrence of a character in a string
 * @s: the sring
 * @c: the character
 *
 * Return: pointer to the character in the string
 */
char *_strchr(char *s, char c)
{
	unsigned int i = 0, n = 0;

	while (s[n] != '\0')
		n++;
	while (i <= n)
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	return (NULL);
}

/**
 * _strstr - our strstr function that locates a string
 * @haystack: the string to search through
 * @needle: the string to search for
 *
 * Return: pointer to the location of the needle
 */
char *_strstr(char *haystack, char *needle)
{
	int i, j, k, n = 0;

	while (needle[n])
		n++;
	for (i = 0; haystack[i]; i++)
	{
		for (j = 0, k = 0; needle[j]; j++, k++)
			if (haystack[i + k] != needle[j])
				break;
		if (j == n)
			return (haystack + i);
	}
	return (NULL);
}
