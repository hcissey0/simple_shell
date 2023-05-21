#include "../shell.h"

int main()
{
	char *vars[]={
		"ls", "cat",
		"seq", "free",
		"/bin/ls", "fff",
		NULL};
	char *ans;
	int i = 0;

	while (vars[i] != NULL)
	{
		ans = find_path(vars[i]);
		printf("%s:\n", vars[i]);
		printf("\t%s\n", ans);
		i++;
	}

	return (0);
}
