#include "../shell.h"

int main()
{
	char str[] = "this is a big thing i have ever had in my life from hte day i was born";
	int i = 1;
	char *tok;

	tok = _strtok(str, " ");
	while (tok != NULL)
	{
		printf("%s\n", tok);
		tok = _strtok(NULL, " ");
	}
	return 0;
}
