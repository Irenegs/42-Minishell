# include "minishell.h"


char *get_heredoc(char *delimiter)
{
	char 	*line;
	char	*aux_1;
	char	*aux_2;

	printf("Delimiter: %s\n", delimiter);
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

char *obtain_delimiter(char *del_str)
{
	char	*delimiter;
	int		len;

	while (*del_str == '<' || is_space(*del_str))
		del_str++;
	len = ft_strlen(del_str);
	if (del_str[0] == '\'' || del_str[0] == '"')
	{
		len = len - 2;
		del_str++;
	}
	delimiter = malloc(len + 2);
	ft_memmove(delimiter, del_str, len);
	delimiter[len] = '\n';
	delimiter[len + 1] = '\0';
	return (delimiter);
}

char	*expand_string(char *s)
{
	char	*expanded;
	char	*aux;
	char	*chunk;
	int		pos;
	int		len;

	if (!s)
		return (NULL);
	expanded = NULL;
	while (s[pos] != '\0')
	{
		if (s[pos] != '$')
		{
			len = len_literal_word(s, pos);
			chunk = ft_substr(s, pos, len);
			pos = pos + len;
			aux = expanded;
			expanded = ft_strjoin(aux, chunk);
			if (aux)
				free(aux);
			if (chunk)
				free(chunk);
		}
		else
		{
			chunk = obtain_variable(s, pos + 1);
			pos += len_literal_word(s, pos + 1) + 1;
			aux = expanded;
			expanded = ft_strjoin(aux, chunk);
			if (aux)
				free(aux);
		}
	}
	return (expanded);
}

void	show_leaks(void)
{
	system("leaks a.out");
}

int	main(int argc, char **argv)
{
	char	*heredoc_text;
	char	*delimiter;
	char	*aux;

	atexit(show_leaks);
	delimiter = obtain_delimiter(argv[1]);
	heredoc_text = get_heredoc(delimiter);
	if (argv[1][0] != '\'' && argv[1][0] != '"')
	{
		aux = heredoc_text;
		heredoc_text = expand_string(aux);
		printf("hola\n");
		free(aux);
	}
	printf("\n====\n%s\n====\n", heredoc_text);
	free(delimiter);
	free(heredoc_text);
	return 0;
}
