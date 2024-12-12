/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:36:46 by irgonzal          #+#    #+#             */
/*   Updated: 2024/12/12 23:32:21 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open(char *filename, int mode)
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

char	*extract_filename(char *s, int *pos, t_mix *data)
{
	char	**element;
	char	*filename;

	element = extract_element(s, *pos, data);
	if (!element)
		return (NULL);
	if (element[1] != NULL)
	{
		ft_out(element);
		return (write_error_null(3));
	}
	filename = ft_strdup(element[0]);
	ft_out(element);
	if (!filename)
		return (write_error_null(1));
	return (filename);
}

static int	get_ouput_fd(char *s, t_mix *data, int *pos)
{
	char	*filename;
	int		fd;

	filename = extract_filename(s, pos, data);
	if (!filename)
		return (-2);
	*pos = locate_char_position_quotes(s, '>');
	if (s[*pos + 1] == '>')
	{
		fd = ft_open(filename, 2);
		(*pos)++;
	}
	else
		fd = ft_open(filename, 1);
	free(filename);
	return (fd);
}

int	extract_output(char *s, t_mix *data)
{
	int		fd;
	int		pos;
	int		aux_fd;

	if (!s)
		return (-2);
	pos = locate_char_position_quotes(s, '>') + 1;
	if (pos == 0)
		return (-1);
	if (s[pos] == '>')
		pos++;
	fd = get_ouput_fd(s, data, &pos);
	if (fd == -2)
		return (-2);
	aux_fd = extract_output(s + pos + 1, data);
	if (aux_fd != -1)
		fd = aux_fd;
	return (fd);
}
