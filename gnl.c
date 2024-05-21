/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:44:36 by irene             #+#    #+#             */
/*   Updated: 2024/05/21 19:44:57 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	bytes = read(fd, buffer, BUFFER_SIZE);
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

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE < 1)
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
