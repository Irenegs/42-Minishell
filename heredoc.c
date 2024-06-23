/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:46:24 by irene             #+#    #+#             */
/*   Updated: 2024/06/23 17:31:20 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_rawtext(char *delimiter)
{
	char	*line;
	char	*aux_1;
	char	*aux_2;

	//ft_interrupt(global_signal);
	aux_2 = readline(">>");//get_next_line(STDIN_FILENO);
	line = NULL;
	while (ft_strncmp(aux_2, delimiter, ft_strlen(delimiter)) != 0
		&& aux_2 != NULL)
	{
		printf("he leido:%s\n", aux_2);
		printf("strncmp:%d\n", ft_strncmp(aux_2, delimiter, ft_strlen(delimiter)));
		printf("del:%s\n", delimiter);
		printf("strlen del:%ld\n", ft_strlen(delimiter));
		aux_1 = line;
		line = ft_strjoin(aux_1, aux_2);
		if (aux_1 != NULL)
			free(aux_1);
		if (aux_2 != NULL)
			free(aux_2);
		aux_2 = readline(">>");//get_next_line(STDIN_FILENO);
	}
	if (aux_2 != NULL)
		free(aux_2);
	return (line);
}

static char	*obtain_delimiter(char *del_str)
{
	char	*delimiter;
	int		len;

	while (*del_str != '<')
		del_str++;
	while (*del_str == '<' || is_space(*del_str))
		del_str++;
	len = len_delimiter(del_str, 0);
	if (del_str[0] == '\'' || del_str[0] == '"')
	{
		len = len - 2;
		del_str++;
	}
	delimiter = malloc(len + 1);//malloc(len + 2);
	ft_memmove(delimiter, del_str, len);
	//delimiter[len] = '\n';
	delimiter[len + 1] = '\0';
	return (delimiter);
}

static char	*expand_string(char *s)
{
	char	*expanded;
	char	*aux;
	char	*chunk;
	int		pos;
	int		len;

	if (!s)
		return (NULL);
	expanded = NULL;
	pos = 0;
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

static int	must_expand(char *s)
{
	if (!s)
		return (0);
	while (*s != '<' && *s != '\0')
		s++;
	while (*s == '<' || is_space(*s) == 1)
		s++;
	if (*s == '"' || *s == '\'')
		return (0);
	return (1);
}

char	*get_heredoc(char *s)
{
	char	*heredoc_text;
	char	*delimiter;
	char	*aux;

	delimiter = obtain_delimiter(s);
	heredoc_text = get_rawtext(delimiter);
	if (must_expand(s) == 1)
	{
		aux = heredoc_text;
		heredoc_text = expand_string(aux);
		free(aux);
	}
	free(delimiter);
	return (heredoc_text);
}

/*
int main(int argc, char **argv)
{
	char *heredoc = get_heredoc(argv[1]);
	printf("4\n");
	printf("%p\n", heredoc);
	free(heredoc);
	return (0);
}*/