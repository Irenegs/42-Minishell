/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:37:34 by irene             #+#    #+#             */
/*   Updated: 2024/12/12 23:32:14 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	get_inputfile_fd(char *s, t_mix *data, int *pos)
{
	char	*filename;
	int		fd;

	filename = extract_filename(s, pos, data);
	if (!filename)
		return (-2);
	fd = ft_open(filename, O_RDONLY);
	free(filename);
	return (fd);
}

int	extract_input(char *s, t_mix *data, int p)
{
	int		fd;
	int		pos;
	int		aux_fd;

	if (!s)
		return (-2);
	pos = locate_char_position_quotes(s, '<') + 1;
	if (pos == 0)
		return (-1);
	if (s[pos] == '<')
		fd = get_heredoc_fd(data->heredocs, p);
	else
		fd = get_inputfile_fd(s, data, &pos);
	if (fd == -2)
		return (-2);
	pos = locate_char_position_quotes(s, '<');
	aux_fd = extract_input(s + pos + 2, data, p);
	if (aux_fd != -1)
		fd = aux_fd;
	return (fd);
}
