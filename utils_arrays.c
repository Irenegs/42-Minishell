/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_arrays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:33:19 by irene             #+#    #+#             */
/*   Updated: 2024/11/21 00:14:26 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_out(char **arr)
{
	int	j;
	
	j = 0;
	
	if (!arr)
		return (NULL);

	while (arr[j])
	{
		arr[j] = NULL;
		free(arr[j]);
		arr[j] = NULL;
		j++;
	}
	free(arr);
	arr = NULL;
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

	if (!array)
		return (NULL);
	size = join_arrays_size(array);
	joined = malloc((size + 1)* sizeof(char *));
	if (!joined)
		return (write_error_null(1));
	fill_joined_array(array, joined);
	joined[size] = NULL;
	return (joined);
}

char	*increment_shlvl(char *env_var)
{
	int		shlvl_value;
	char	*new_shlvl;
	char	*new_shlvl_value;

	if (ft_strncmp(env_var, "SHLVL=", 6) == 0)
	{
		shlvl_value = ft_atoi(env_var + 6) + 1;
		new_shlvl_value = ft_itoa(shlvl_value);
		if (!new_shlvl_value)
			return (write_error_null(1));
		new_shlvl = (char *)malloc(7 + ft_strlen(new_shlvl_value));
		if (!new_shlvl)
		{
			free(new_shlvl_value);
			return (write_error_null(1));
		}
		ft_strlcpy(new_shlvl, "SHLVL=", 7);
		ft_strlcat(new_shlvl, new_shlvl_value,
			7 + ft_strlen(new_shlvl_value));
		free(new_shlvl_value);
		return (new_shlvl);
	}
	return (env_var);
}

char **free_partial_array(char **array, int filled)
{
   int i = 0;

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