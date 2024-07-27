/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 22:08:38 by pablo             #+#    #+#             */
/*   Updated: 2024/07/27 18:14:59 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_env_entry(const char *key, const char *value)
{
	size_t	key_len;
	size_t	entry_len;
	size_t	j;
	size_t	k;
	char	*entry;

	if (!key)
		return (NULL);
	key_len = ft_strlen(key);
	entry_len = key_len + ft_strlen(value) + 2;
	entry = (char *)malloc(entry_len);
	if (!entry)
		return (write_error_null(1));
	j = 0;
	while (j < key_len)
	{
		entry[j] = key[j];
		j++;
	}
	entry[j++] = '=';
	k = 0;
	while (k < ft_strlen(value))
		entry[j++] = value[k++];
	entry[j] = '\0';
	return (entry);
}

char	**new_entry(char **env, const char *key, const char *value, int size)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc((size + 2) * sizeof(char *));
	if (!new_env)
		return (write_error_null(1));
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = create_env_entry(key, value);
	if (!new_env[i])
	{
		free(new_env);
		return (NULL);
	}
	new_env[i + 1] = NULL;
	return (new_env);
}

char	**update_entry(char **env, int i, const char *key, const char *value)
{
	char	*new_entry;

	new_entry = create_env_entry(key, value);
	if (new_entry)
	{
		free(env[i]);
		env[i] = new_entry;
	}
	return (env);
}

int is_special_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else
		return (0);
}
