/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:35:07 by pablgarc          #+#    #+#             */
/*   Updated: 2024/07/30 20:00:20 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_env_index(char **env, const char *key)
{
	size_t	key_len;
	int		i;

	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	**au_env(char **env, const char *key, const char *value)
{
	int		index;
	int		size;
	char	**new_env;

	index = find_env_index(env, key);
	if (index != -1)
		return (update_entry(env, index, key, value));
	size = 0;
	while (env[size])
		size++;
	new_env = new_entry(env, key, value, size);
	if (!new_env)
		return (NULL);
	free(env);
	return (new_env);
}

char	**copy_env_without_entry(char **env, int index, int size)
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

char	**remove_env(char **env, const char *key)
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

int	valid_varname(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] != '\0')
	{
		if (i == 0 && ft_isdigit(str[i]) != 0)
			return (0);
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
