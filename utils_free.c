/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:11:18 by irene             #+#    #+#             */
/*   Updated: 2024/12/13 00:16:01 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char ***arr)
{
	int	i;
	int	j;

	i = 0;
	while (arr && arr[i])
	{
		j = 0;
		while (arr[i] && arr[i][j])
		{
			free(arr[i][j]);
			j++;
		}
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**ft_out_exception(char **arr, int n)
{
	int	j;

	j = 0;
	if (!arr)
		return (NULL);
	while (arr[j] || j == n)
	{
		if (j != n)
			free(arr[j]);
		j++;
	}
	free(arr);
	return (NULL);
}

char	**ft_out(char **arr)
{
	int	j;

	j = 0;
	if (!arr)
		return (NULL);
	while (arr[j])
	{
		free(arr[j]);
		j++;
	}
	free(arr);
	return (NULL);
}

char	**free_partial_array(char **array, int filled)
{
	int	i;

	i = 0;
	if (!array)
		return (NULL);
	while (i < filled)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}
