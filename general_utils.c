/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:06:33 by irgonzal          #+#    #+#             */
/*   Updated: 2024/09/15 16:45:12 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_quote(char c)
{
    if (c == '\'' || c == '"')
        return ((int) c);
    return (0);
}

int	is_space(char c)
{
	if (c == 32 || (c < 14 && c > 8) || c == '\0')
		return (1);
	return (0);
}

int	is_separator(char c)
{
	return ((c != ' ' && c != '<' && c != '>' && c != '|'));
}

void	manage_quotes(int *quotes, char c)
{
	if (c == *quotes && *quotes != 0)
		*quotes = 0;
	else if (*quotes == 0 && (c == '\'' || c == '"'))
		*quotes = c;
}

char	**ft_out(char **arr)
{
	int	j;

	j = 0;
	while (arr[j])
	{
		free(arr[j]);
		j++;
	}
	free(arr);
	return (NULL);
}

int	join_arrays_size(char ***array)
{
	int size;
	int	i;
	int	j;

	if (!array)
		return (0);
	size = 0;
	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			j++;
			size++;
		}
		i++;
	}
	return (size);
}

void	fill_joined_array(char ***array, char **joined)
{
	int size;
	int	i;
	int	j;

	if (!array || !joined)
		return ;
	size = 0;
	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			joined[size] = array[i][j];
			j++;
			size++;
		}
		i++;
	}
}

char **join_arrays(char ***array)
{
	int		size;
	char	**joined;
	printf("join_arrays\n");
	if (!array)
		return (NULL);
	size = join_arrays_size(array);
	joined = malloc(size * sizeof(char *));
	if (!joined)
		return (write_error_null(1));
	fill_joined_array(array, joined);
	return (joined);
}