# include <stdlib.h>
# include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	char *s = argv[1];
	char *t = getenv(s);
	if (t == 0)
		t = "";
	printf("Variable %s => %s\n", s, t);
	printf("Pointer %p\n", t);
}