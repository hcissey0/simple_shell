#include "../shell.h"

/**
 * main - testingthe remove_newline function
 *
 * Return: Always 0
 */
int main(void)
{
	char *str = malloc(sizeof(char) * 13);

	strcpy(str, "Hello world\n");
	printf("Before remove_newline\n");
	printf("%s", str);
	printf("After remove_newline\n");
	remove_newline(&str);
	printf("%s", str);

	free(str);
	return 0;
}
