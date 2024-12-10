/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:23:21 by irene             #+#    #+#             */
/*   Updated: 2024/12/10 21:38:51 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		new_env[j] = ft_strdup(env[i]);
		if (!new_env[j])
		{
			while (j-- > 0)
				free(new_env[j]);
			free(new_env);
			return (NULL);
		}
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
		{
			perror("unset");
			return (1);
		}
		i++;
	}
	return (0);
}
