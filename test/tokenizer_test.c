#include "../shell.h"

/**
 * main - testing the tokenizer function
 *
 * Return: 0 onsuccess otherwise 1
 */
int main()
{
	int i = 0;
	char **res, *delim = "::", *str = malloc(sizeof(char) * 20);
	strcpy(str, "i::am::new::here");

	printf("String before tokenizer: %s\n", str);
	res = tokenizer(str, delim);
	if (res == NULL)
	{
		printf("tokenizer failed");
		return (1);
	}
	printf("After tokenizer:\n");
	while (res[i] !=  NULL)
		printf("%s\n", res[i++]);

	free(str);

	free(res);

	return (0);
}
