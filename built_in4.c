/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 22:08:38 by pablo             #+#    #+#             */
/*   Updated: 2024/05/30 22:10:42 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *create_env_entry(const char *key, const char *value)
{
    size_t key_len;
    size_t entry_len;
    size_t j;
    size_t k;
    char *entry;

    key_len = ft_strlen(key);
    entry_len = key_len + ft_strlen(value) + 2;
    entry = (char *)malloc(entry_len);
    if (!entry)
        return NULL;

    j = 0;
    while (j < key_len)
    {
        entry[j] = key[j];
        j++;
    }
    entry[j++] = '=';
    k = 0;
    while (k < ft_strlen(value))
    {
        entry[j++] = value[k++];
    }
    entry[j] = '\0';

    return entry;
}

char **copy_env_with_new_entry(char **env, const char *key, const char *value, int size)
{
    char **new_env = (char **)malloc((size + 2) * sizeof(char *));
    if (!new_env)
        return NULL;

    int i = 0;
    while (env[i])
    {
        new_env[i] = env[i];
        i++;
    }

    new_env[i] = create_env_entry(key, value);
    if (!new_env[i])
    {
        free(new_env);
        return NULL;
    }

    new_env[i + 1] = NULL;
    return new_env;
}

char **update_existing_entry(char **env, int index, const char *key, const char *value)
{
    free(env[index]);
    env[index] = create_env_entry(key, value);
    if (!env[index])
        return NULL;
    return env;
}
