/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_arrays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:33:19 by irene             #+#    #+#             */
/*   Updated: 2024/09/22 17:50:07 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	join_arrays_size(char ***array)
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

static void	fill_joined_array(char ***array, char **joined)
{
	int size;
	int	i;
	int	j;
	printf("fill_joined_array\n");
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
			printf("joined[size]:%s\n", joined[size]);
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

	if (!array)
		return (NULL);
	printf("array[0][0]:%s\n", array[0][0]);
	size = join_arrays_size(array);
	joined = malloc(size * sizeof(char *));
	if (!joined)
		return (write_error_null(1));
	fill_joined_array(array, joined);
	return (joined);
}
