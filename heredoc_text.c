/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:46:24 by irene             #+#    #+#             */
/*   Updated: 2024/08/28 17:28:31 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_mult(char *ptr1, char *ptr2)
{
	free(ptr1);
	free(ptr2);
}

static char	*get_rawtext(char *del)
{
	char	*line;
	char	*aux_1;
	char	*aux_2;

	ft_signals_hd();
	line = malloc(1 * sizeof(char));
	if (!line)
		return (write_error_null(1));
	line[0] = '\0';
	aux_2 = readline("Heredoc>");
	while (aux_2 != NULL && ft_strncmp(aux_2, del, ft_strlen(del) + 1) != 0)
	{
		aux_1 = ft_strjoin(line, aux_2);
		free_mult(line, aux_2);
		if (!aux_1)
			return (write_error_null(1));
		line = ft_strjoin(aux_1, "\n");
		free(aux_1);
		if (!line)
			return (write_error_null(1));
		aux_2 = readline("Heredoc>");
	}
	free(aux_2);
	ft_signals_running();
	return (line);
}

static char	*get_heredoc(char *s, t_mix *data)
{
	char	*heredoc_text;
	char	*delimiter;
	char	*aux;

	delimiter = obtain_delimiter(s);
	if (!delimiter)
		return (write_error_null(1));
	heredoc_text = get_rawtext(delimiter);
	if (heredoc_text == NULL)
	{
		free(delimiter);
		return (NULL);
	}
	if (must_expand(s, heredoc_text) == 1)
	{
		aux = heredoc_text;
		heredoc_text = expand_heredoc(aux, data);
		free(aux);
	}
	free(delimiter);
	return (heredoc_text);
}

int	write_hd_file(char *s, int hd_number, t_mix *data)
{
	char	*heredoc_text;
	int		fd;
	int		ret_value;

	ret_value = 0;
	if (!s || !data->heredocs[hd_number] || !data)
		return (-1);
	heredoc_text = get_heredoc(s, data);
	if (heredoc_text == NULL)
		return (-1);
	fd = open(data->heredocs[hd_number], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		free(heredoc_text);
		return (perror_int(1));
	}
	if (write(fd, heredoc_text, ft_strlen(heredoc_text)) == -1)
		ret_value = write_error_int(2, 1);
	close(fd);
	free(heredoc_text);
	return (ret_value);
}
