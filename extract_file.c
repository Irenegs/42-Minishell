/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:36:46 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/27 20:08:29 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_open(char *filename, int mode)
{
	int	fd;

	if (!filename || mode < 0 || mode > 2)
		return (-2);
	if (mode == 0)
		fd = open(filename, O_RDONLY);
	else if (mode == 1)
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror_int(-2));
	return (fd);
}

int	locate_char_position_quotes(char *s, char c)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] == c && quotes == 0)
			return (i);
		if (s[i] == quotes && quotes != 0)
			quotes = 0;
		else if (quotes == 0 && (s[i] == '\'' || s[i] == '"'))
			quotes = s[i];
		i++;
	}
	return (-1);
}


int	locate_char_position(char *s, char c)
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

static int	get_heredoc_fd(char	**heredocs, int p)
{
	int	fd;

	if (p == -1)
		p = 0;
	if (!heredocs || !heredocs[p])
		return (-2);
	fd = ft_open(heredocs[p], O_RDONLY);
	return (fd);
}

int	extract_input(char *s, t_mix *data, int p)
{
	int		fd;
	int		pos;
	char	*filename;
	int		aux_fd;

	if (!s)
		return (-2);
	pos = locate_char_position_quotes(s, '<');
	if (pos == -1)
		return (-1);
	if (s[pos + 1] == '<')
		fd = get_heredoc_fd(data->heredocs, p);
	else
	{
		filename = extract_element(s, &pos, data);
		if (!filename)
			return (write_error_int(1, -2));
		fd = ft_open(filename, O_RDONLY);
		free(filename);
	}
	aux_fd = extract_input(s + pos + 2, data, p);
	if (aux_fd != -1 && fd != -2)
		fd = aux_fd;
	return (fd);
}

int	extract_output(char *s, t_mix *data)
{
	int		fd;
	int		pos;
	char	*filename;
	int		aux_fd;

	if (!s)
		return (-2);
	pos = locate_char_position_quotes(s, '>');
	if (pos == -1)
		return (-1);
	if (s[pos + 1] == '>')
		pos++;
	filename = extract_element(s, &pos, data);
	if (!filename)
		return (write_error_int(1, -2));
	if (pos == locate_char_position(s, '>'))
		fd = ft_open(filename, 1);
	else
		fd = ft_open(filename, 2);
	free(filename);
	aux_fd = extract_output(s + pos + 1, data);
	if (aux_fd != -1 && fd != -2)
		fd = aux_fd;
	return (fd);
}
