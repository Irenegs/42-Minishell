/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:44:36 by irene             #+#    #+#             */
/*   Updated: 2024/06/23 17:37:20 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	find_br(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	return (i);
}

ssize_t	read_line(char **rem, int fd)
{
	ssize_t	bytes;
	char	*buffer;
	char	*line;

	//ft_signals_running();
	buffer = malloc((11) * sizeof(char));
	if (!buffer)
		return(-1);
	bytes = read(fd, buffer, 10);
	if (bytes >= 0)
	{
		buffer[bytes] = '\0';
		line = ft_strjoin(*rem, buffer);
		free(*rem);
		*rem = line;
	}
	free(buffer);
	return (bytes);
}

void	prepare_line(char *array[], char *rem)
{
	size_t	br;

	br = find_br(rem);
	if (!rem || rem[0] == '\0')
	{
		array[0] = NULL;
		array[1] = NULL;
	}
	else if (rem[br] != '\n')
	{
		array[0] = ft_substr(rem, 0, ft_strlen(rem));
		array[1] = NULL;
	}
	else
	{
		array[0] = ft_substr(rem, 0, br + 1);
		array[1] = ft_substr(rem, br + 1, ft_strlen(rem) - br);
	}
}

char	*get_next_line(int fd)
{
	static char	*rem = NULL;
	char		*array[2];
	ssize_t		bytes;

	if (fd < 0 || fd > FOPEN_MAX)
		return (NULL);
	if (!rem || rem[find_br(rem)] != '\n')
	{
		bytes = read_line(&rem, fd);
		while (bytes > 0 && rem[find_br(rem)] != '\n')
		{
			bytes = read_line(&rem, fd);
		}
		if (bytes < 0)
		{
			free(rem);
			rem = NULL;
			return (NULL);
		}
	}
	prepare_line(array, rem);
	free(rem);
	rem = array[1];
	return (array[0]);
}
