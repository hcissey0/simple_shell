#include "../shell.h"

/**
 * main - testing _getenv
 *
 * Return: Always 0
 */
int main(void)
{
	int i = 0;
	char *var[] = {
		"PATH", "LS_COLORS",
		"HOME", "ROOT", "LC_ALL",
		NULL};
	char *value;

	while (var[i])
	{
		value = _getenv(var[i]);
		printf("%s:\n%s\n", var[i++], value);
	}
	return (0);
}
