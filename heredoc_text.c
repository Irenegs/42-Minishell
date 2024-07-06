/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:46:24 by irene             #+#    #+#             */
/*   Updated: 2024/07/06 14:49:54 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_rawtext(char *delimiter)
{
	char	*line;
	char	*aux_1;
	char	*aux_2;

	ft_signals_new ();
	//ft_ignore_sigquit();
	aux_2 = get_next_line(STDIN_FILENO);
	line = malloc(1 * sizeof(char));
	line[0] = '\0';
	while (aux_2 != NULL && ft_strncmp(aux_2, delimiter, ft_strlen(delimiter)) != 0)
	{
		aux_1 = line;
		line = ft_strjoin(aux_1, aux_2);
		free(aux_1);
		free(aux_2);
		aux_2 = get_next_line(STDIN_FILENO);
	}
	if (aux_2 == NULL)
	{
		free(line);
		return (NULL);
	}
	free(aux_2);
	ft_sig_def();// Restaura el manejador de señal predeterminado después del heredoc
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
	if (heredoc_text == NULL)
	{
		free(delimiter);
		return (NULL); // Interrupción manejada aquí
	}
	if (must_expand(s, heredoc_text) == 1)
	{
		aux = heredoc_text;
		heredoc_text = expand_string(aux);
		free(aux);
	}
	free(delimiter);
	return (heredoc_text);
}

int	write_hd_file(char *s, char *filename)
{
	char	*heredoc_text;
	int		fd;
	int		ret_value;

	ret_value = 0;
	if (!s || !filename)
		return (-1);
	heredoc_text = get_heredoc(s);
	if (heredoc_text == NULL)
	{
		printf("\nHeredoc interrupted by SIGINT\n"); // Mensaje de interrupción
		return (-1); // Interrupción manejada aquí
	}
	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		free(heredoc_text);
		return (1);
	}
	if (write(fd, heredoc_text, ft_strlen(heredoc_text)) == -1)
		ret_value = 1;
	close(fd);
	free(heredoc_text);
	return (ret_value);
}
/*
void show_leaks(void)
{
	system("leaks a.out");
}
int main(int argc, char **argv)
{
	atexit(show_leaks);
	if (argc >1)
	{
		printf("hola\n");
		char *heredoc = get_heredoc(argv[1]);
		printf("4\n");
		printf("%s\n", heredoc);
		free(heredoc);
	}
	return (0);
}
*/
/*
BIEN, PERO INCUMPLE NORMA

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
	{
		if (line == NULL)
		{
			line = malloc(1 * sizeof(char));
			line[0] = '\0';
		}
		free(aux_2);
	}
	return (line);
}
*/
/*
VERSIÓN ANTERIOR CON READLINE, FALTAN LOS SALTOS DE LINEA

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
