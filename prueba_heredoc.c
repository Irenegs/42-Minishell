# include "minishell.h"


char *get_heredoc(char *delimiter)
{
	char 	*line;
	char	*aux_1;
	char	*aux_2;

	aux_2 = get_next_line(1);
	line = NULL;
	while (ft_strncmp(aux_2, delimiter, ft_strlen(delimiter)) != 0 && aux_2 != NULL)
	{
		aux_1 = line;
		line = ft_strjoin(aux_1, aux_2);
		if (aux_1 != NULL)
			free(aux_1);
		if (aux_2 != NULL)
			free(aux_2);
		aux_2 = get_next_line(1);
	}
	if (aux_2 != NULL)
		free(aux_2);
	//line[ft_strlen(line) - 1] = '\0';
	return (line);
}

void	show_leaks(void)
{
	system("leaks a.out");
}

int	main(int argc, char **argv)
{
	char *result;
	char *delimiter;

	atexit(show_leaks);
	delimiter = malloc(ft_strlen(argv[1]) + 2);
	ft_memmove(delimiter, argv[1], ft_strlen(argv[1]));
	delimiter[ft_strlen(argv[1])] = '\n';
	delimiter[ft_strlen(argv[1]) + 1] = '\0';
	result = get_heredoc(delimiter);
	printf("%s\n====\n", result);
	free(delimiter);
	free(result);
	return 0;
}

/*
Falta distinguir en el delimitador si está o no entrecomillado para luego expandirlo o no.
*/