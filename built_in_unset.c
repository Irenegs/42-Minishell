/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:23:21 by irene             #+#    #+#             */
/*   Updated: 2024/11/16 20:26:37 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**copy_env_without_entry(char **env, int index, int size)
{
	char	**new_env;
	int		j;
	int		i;

	i = 0;
	j = 0;
	new_env = (char **)malloc(size * sizeof(char *));
	if (!new_env)
		return (write_error_null(1));
	while (i < index)
	{
		new_env[j] = env[i];
		i++;
		j++;
	}
	free(env[index]);
	while (env[++i])
	{
		new_env[j] = env[i];
		j++;
	}
	new_env[j] = NULL;
	return (new_env);
}

static char	**remove_env(char **env, const char *key)
{
	int		index;
	int		size;
	char	**new_env;

	size = 0;
	index = find_env_index(env, key);
	if (index == -1)
		return (env);
	while (env[size])
		size++;
	new_env = copy_env_without_entry(env, index, size);
	if (!new_env)
		return (NULL);
	free(env);
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
