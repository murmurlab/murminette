#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	char *line;
	for (size_t i = 0; i < atoi(argv[2]); i++)
	{
		line=get_next_line(atoi(argv[1]));
		if (line != NULL)
			printf("%s", line);
		else
			printf("(null)\n");
		free(line);
	}
	return 0;
}
