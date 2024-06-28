/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:46:24 by irene             #+#    #+#             */
/*   Updated: 2024/06/28 19:55:54 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_rawtext(char *delimiter)
{
	char	*line;
	char	*aux_1;
	char	*aux_2;

	aux_2 = get_next_line(STDIN_FILENO);
	line = NULL;
	while (ft_strncmp(aux_2, delimiter, ft_strlen(delimiter)) != 0
		&& aux_2 != NULL)
	{
		aux_1 = line;
		line = ft_strjoin(aux_1, aux_2);
		if (aux_1 != NULL)
			free(aux_1);
		if (aux_2 != NULL)
			free(aux_2);
		aux_2 = get_next_line(STDIN_FILENO);
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
	delimiter = malloc(len + 2);
	ft_memmove(delimiter, del_str, len);
	delimiter[len] = '\n';
	delimiter[len + 1] = '\0';
	return (delimiter);
}

static char	*get_heredoc(char *s)
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

int	write_heredoc_file(char *s, char *filename)
{
	char	*heredoc_text;
	int		fd;

	if (!s || !filename)
		return (-1);
	heredoc_text = get_heredoc(s);
	if (!heredoc_text)
		return (1);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(heredoc_text);
		return (1);
	}
	write(fd, heredoc_text, ft_strlen(heredoc_text));
	close(fd);
	free(heredoc_text);
	return (0);
}

/*
int main(int argc, char **argv)
{
	char *heredoc = get_heredoc(argv[1]);
	printf("4\n");
	printf("%p\n", heredoc);
	free(heredoc);
	return (0);
}
*/
/*
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
		printf("strncmp:%d\n", ft_strncmp(aux_2, delimiter, \
		ft_strlen(delimiter)));
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
*/
