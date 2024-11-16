/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:35:07 by pablgarc          #+#    #+#             */
/*   Updated: 2024/11/16 20:26:40 by irene            ###   ########.fr       */
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
