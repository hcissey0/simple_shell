#include "../shell.h"

int main()
{
	char *line;
	size_t len;
	ssize_t rd;
	FILE *p = fopen("new.txt", "r");

	while ((rd = _getline(&line, &len, p)) != -1)
		printf("%s", line);
	return 0;
}
