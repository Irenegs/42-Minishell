/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:23:21 by irene             #+#    #+#             */
/*   Updated: 2024/12/11 22:32:48 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_env(char **new_env, char **env, int src_ind, int dest_ind)
{
	new_env[dest_ind] = ft_strdup(env[src_ind]);
	if (!new_env[dest_ind])
	{
		while (dest_ind-- > 0)
			free(new_env[dest_ind]);
		free(new_env);
		return (write_error_int(1, 1));
	}
	return (0);
}

static char	**copy_env_without_entry(char **env, int index, int size)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = (char **)malloc(size * sizeof(char *));
	if (!new_env)
		return (write_error_null(1));
	i = 0;
	j = 0;
	while (i < size - 1)
	{
		if (i == index)
		{
			i++;
			continue ;
		}
		if (copy_env(new_env, env, i, j) != 0)
			return (NULL);
		i++;
		j++;
	}
	new_env[j] = NULL;
	return (new_env);
}

static void	free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

static char	**remove_env(char **env, const char *key)
{
	int		index;
	int		size;
	char	**new_env;

	index = find_env_index(env, key);
	if (index == -1)
		return (env);
	size = 0;
	while (env[size])
		size++;
	new_env = copy_env_without_entry(env, index, size);
	if (!new_env)
		return (NULL);
	free_env(env);
	return (new_env);
}

int	ft_unset(t_mix *data, char **command)
{
	int	i;

	i = 1;
	if (!command[1])
		return (0);
	while (command[i])
	{
		data->m_env = remove_env(data->m_env, command[i]);
		if (!data->m_env)
			return (1);
		i++;
	}
	return (0);
}
