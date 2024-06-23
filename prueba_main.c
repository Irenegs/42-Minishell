# include "minishell.h"

void show_leaks(void)
{
	system("leaks a.out");
}

int main(int argc, char **argv)
{
	char	*s = argv[1];

	atexit(show_leaks);
	if (argc == 1)
		return (1);
	parse_and_execute(s);
	return (0);
}