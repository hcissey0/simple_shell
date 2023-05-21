#include "../shell.h"

int main()
{
	int i = 0;
	char *vars[] = {"ls", "cat", "seq", "/bin/ls", "free", NULL};

	while (vars[i] != NULL)
		printf("%d:\n%s\n",i, find_path(vars[i++]));
	return 0;
}
