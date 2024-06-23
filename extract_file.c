/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:36:46 by irgonzal          #+#    #+#             */
/*   Updated: 2024/06/22 19:14:54 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	locate_char_position(char *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int	get_heredoc_fd(char *s)
{
	char	*heredoc_text;
	int		fd;

	heredoc_text = get_heredoc(s);
	fd = open(".tmpfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, heredoc_text, ft_strlen(heredoc_text));
	close(fd);
	fd = open(".tmpfile", O_RDONLY);
	free(heredoc_text);
	return (fd);
}

int	extract_input(char *s)
{
	int		fd;
	int		pos;
	char	*filename;
	int		aux_fd;

	if (!s)
		return (-2);
	pos = locate_char_position(s, '<');
	if (pos == -1)
		return (-1);
	if (s[pos + 1] == '<')
		fd = get_heredoc_fd(s + pos);
	else
	{
		filename = extract_element(s, pos);
		if (!filename)
			return (-2);
		fd = open(filename, O_RDONLY);
		free(filename);
	}
	aux_fd = extract_input(s + pos + 2);
	if (aux_fd > -1)
		fd = aux_fd;
	return (fd);
}

int	extract_output(char *s)
{
	int		fd;
	int		pos;
	char	*filename;
	int		aux_fd;

	if (!s)
		return (-2);
	pos = locate_char_position(s, '>');
	if (pos == -1)
		return (-1);
	if (s[pos + 1] == '>')
		pos++;
	filename = extract_element(s, pos);
	if (!filename)
		return (-2);
	if (pos == locate_char_position(s, '>'))
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	free(filename);
	aux_fd = extract_output(s + pos + 1);
	if (aux_fd > -1)
		fd = aux_fd;
	return (fd);
}
