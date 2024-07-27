/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:31:25 by pablo             #+#    #+#             */
/*   Updated: 2024/05/23 23:00:52 by pablo            ###   ########.fr       */
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

char	**add_or_update_env(char **env, const char *key, const char *value)
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
		return (NULL);
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

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else
		return (0);
}
