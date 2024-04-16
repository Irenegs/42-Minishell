
# include "minishell.h"

int main(int argc, char **argv)
{
	char 	*s = argv[0];
	t_word	*parseo = parser(s);

	int i = 0;
	while (parseo != NULL)
	{
		if (parseo->function == INPUT)
			printf("Input %s\n", parseo->content);
		else if (parseo->function == COMMAND)
			printf("Command %s\n", parseo->content);
		else if (parseo->function == ARG)
			printf("Arg %s\n", parseo->content);
		else if (parseo->function == OUTPUT)
			printf("OUTPUT %s\n", parseo->content);
		else if (parseo->function == DELIMITER)
			printf("Delimiter %s\n", parseo->content);
		parseo = parseo->next;
	}
	return (0);
}