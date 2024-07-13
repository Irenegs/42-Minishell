/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:46:24 by irene             #+#    #+#             */
/*   Updated: 2024/07/12 19:52:41 by irene            ###   ########.fr       */
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
	aux_2 = readline("Heredoc>");
	line = malloc(1 * sizeof(char));
	line[0] = '\0';
	while (aux_2 != NULL && ft_strncmp(aux_2, delimiter, ft_strlen(delimiter)) != 0)
	{
		aux_1 = ft_strjoin(line, aux_2);
		free(line);
		free(aux_2);
		line = ft_strjoin(aux_1, "\n");
		free(aux_1);
		aux_2 = readline("Heredoc>");
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
	delimiter = malloc(len + 1);
	ft_memmove(delimiter, del_str, len);
	delimiter[len] = '\0';
	return (delimiter);
}

static char	*get_heredoc(char *s, t_mix *data)
{
	char	*heredoc_text;
	char	*delimiter;
	char	*aux;

	delimiter = obtain_delimiter(s);
	heredoc_text = get_rawtext(delimiter);
	if (heredoc_text == NULL)
	{
		free(delimiter);
		return (NULL);//Interrupción manejada aquí
	}
	if (must_expand(s, heredoc_text) == 1)
	{
		aux = heredoc_text;
		heredoc_text = expand_string(aux, data);
		free(aux);
	}
	free(delimiter);
	return (heredoc_text);
}

int	write_hd_file(char *s, char *filename, t_mix *data)
{
	char	*heredoc_text;
	int		fd;
	int		ret_value;

	ret_value = 0;
	if (!s || !filename)
		return (-1);
	heredoc_text = get_heredoc(s, data);
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
