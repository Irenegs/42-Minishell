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

//gcc -o beta built_in2.c built_in.c built_in3.c built_in4.c  struct.c main.c libft/libft.a -lreadline


int find_env_index(char **env, const char *key)
{
    size_t key_len = ft_strlen(key);
    int i = 0;

    while (env[i])
    {
        if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
            return i;
        i++;
    }
    return -1;
}

char **add_or_update_env(char **env, const char *key, const char *value)
{
    int index = find_env_index(env, key);
    if (index != -1)
    {
        return update_existing_entry(env, index, key, value);
    }

    int size = 0;
    while (env[size])
        size++;

    char **new_env = copy_env_with_new_entry(env, key, value, size);
    if (!new_env)
        return NULL;

    free(env);
    return new_env;
}

char **copy_env_without_entry(char **env, int index, int size)
{
    char **new_env = (char **)malloc(size * sizeof(char *));
    if (!new_env)
        return NULL;

    int j = 0;
    int i = 0;

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

    return new_env;
}

char **remove_env(char **env, const char *key)
{
    int index = find_env_index(env, key);
    if (index == -1)
        return env;

    int size = 0;
    while (env[size])
        size++;

    char **new_env = copy_env_without_entry(env, index, size);
    if (!new_env)
        return NULL;

    free(env);
    return new_env;
}


/*
void prompt(t_mix *data)
{
    char *input;
    char **argv;

    while (1)
    {
        input = readline("Minishell: ");
        if (*input)
            add_history(input);
        if(*input != '\0')
        {
            argv = ft_split(input, ' ');
            if (argv)
            {
                data->m_argv = argv;
                execute_builtin(argv, data);
                free(argv);
            }
            free(input);
        }
    }
}

int main(int argc, char **argv, char **envp)
{
    t_mix data;

    if (argc != 1 || !argv)
       return (1);

    ft_init_mix(&data);
    ft_fill_struct(&data, argc, argv, envp);
    prompt(&data);
    ft_free_env(data.m_env);
    ft_free_env(data.m_argv);
    return (0);
}
*/