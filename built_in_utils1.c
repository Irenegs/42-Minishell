/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 22:08:38 by pablo             #+#    #+#             */
/*   Updated: 2024/07/28 19:39:36 by pablgarc         ###   ########.fr       */
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

int	ft_isnum(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	c;
	unsigned char	d;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		c = (unsigned char)s1[i];
		d = (unsigned char)s2[i];
		if (c != d)
			return (c - d);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
