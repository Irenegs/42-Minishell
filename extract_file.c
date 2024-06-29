/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:36:46 by irgonzal          #+#    #+#             */
/*   Updated: 2024/06/29 16:37:42 by irgonzal         ###   ########.fr       */
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

static int	get_heredoc_fd(char	**heredocs, int p)
{
	int	fd;

	if (p == -1)
		p = 0;
	if (!heredocs || !heredocs[p])
		return (-2);
	printf("heredocs[%d]: %s\n", p, heredocs[p]);
	fd = open(heredocs[p], O_RDONLY);
	printf("heredoc fd %d\n", fd);
	return (fd);
}

int	extract_input(char *s, char	**heredocs, int p)
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
		fd = get_heredoc_fd(heredocs, p);
	else
	{
		filename = extract_element(s, pos);
		if (!filename)
			return (-2);
		fd = open(filename, O_RDONLY);
		free(filename);
	}
	printf("input fd %d\n", fd);
	aux_fd = extract_input(s + pos + 2, heredocs, p);
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
