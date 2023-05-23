#include "../shell.h"

int main()
{
	char *line[] = {
		"ls -la", "chat hello",
		"echo plees", "seq 1 10",
		"mmmm", NULL};
	char **tokens, *temp;
	int i = 0;
	while (line[i] != NULL)
	{
		temp = strdup(line[i]);
		tokens = tokenizer(temp, " ");
		run_command(tokens);
		i++;
		free(temp);
		free(tokens);
	}

	return 0;
}
