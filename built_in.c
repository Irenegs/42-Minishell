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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_mix
{
	char	**m_env;
	char	**m_path;
	char	**m_argv;

}				t_mix;

#define MAX_argv 100  // Número máximo de argumentos
//uso fprintf para probar, y las funciones de la libft version normal
//compilar gcc -o built built_in.c -lreadline

void	ft_free_env(char **env)
{
	int	i;

	i = -1;
	if (!env)
		return ;
	while (env[++i])
	{
		free(env[i]);
	}
	*env = NULL;
	free(env);
}

//inicializar la struct
void	ft_init_mix(t_mix *data)
{
	data->m_path = NULL;
	data->m_env = NULL;
	data->m_argv = NULL;

}

//hace una copia del entorno
char	**ft_copy_env(char **envp)
{
	char	**env_copy;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (envp[j])
		j++;
	env_copy = (char **)malloc((j + 1) * sizeof(char *));
	if (!env_copy)
		return (ft_free_env(env_copy), NULL);
	 while (i < j)
    {
        env_copy[i] = strdup(envp[i]);
        if (!env_copy[i])
        {
            while (i--)
                free(env_copy[i]);
            free(env_copy);
            return NULL;
        }
        i++;
    }
    env_copy[j] = NULL;
    return env_copy;
}

//hace copia de argumentos
char  **ft_copy_argv(int argc, char **argv)
{
    char **new_argv;
    int i;
    int j;

    new_argv = (char **)malloc((argc + 1) * sizeof(char *));
    if (!new_argv)
    {
        perror("Error en la asignación de memoria");
        return (NULL);
    }
    i = 0;
    while ( i < argc)
    {
        new_argv[i] = strdup(argv[i]);
        if (!new_argv[i])
        {
            while (i--)
                free(new_argv[i]);
            free(new_argv);
            return NULL;
        }
        i++;
    }
    new_argv[argc] = NULL;
    return (new_argv);
}

//pasamos los datos a la struct
void	ft_fill_struct(t_mix *data, int argc, char **argv, char **envp)
{
	data->m_env = ft_copy_env(envp);
    data->m_argv = ft_copy_argv(argc, argv);
}


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	c;
	unsigned char	d;

	i = 0;
	if (n == 0)
		return (0);
	c = (unsigned char)s1[0];
	d = (unsigned char)s2[0];
	while (c == d && i < n - 1 && c != '\0' && d != '\0')
	{
		i++;
		c = (unsigned char)s1[i];
		d = (unsigned char)s2[i];
	}
	if (c == '\0' && d != '\0')
		return (-1);
	if (c != '\0' && d == '\0')
		return (1);
	return (c - d);
}

int ft_strcmp(const char *s1, const char *s2)
{
    size_t i = 0;

    while (s1[i] != '\0' && s2[i] != '\0')
    {
        unsigned char c = (unsigned char)s1[i];
        unsigned char d = (unsigned char)s2[i];

        if (c != d)
            return c - d;

        i++;
    }

    return (unsigned char)s1[i] - (unsigned char)s2[i];
}


static int	ft_j_words(const char *str, char c)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (*str)
	{
		if (*str != c && i == 0)
		{
			i = 1;
			j++;
		}
		else if (*str == c)
			i = 0;
		str++;
	}
	return (j);
}

static char	*ft_word( const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (0);
	while (start < end)
	{
		word[i] = str [start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

char	*free_alocate(char **split, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(split[i]);
	}
	free(split);
	return (NULL);
}

char	**end(char **split, int j)
{
	split[j] = NULL;
	return (split);
}	

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		k;
	char	**split;

	split = malloc (sizeof(char *) * (ft_j_words (s, c) + 1));
	if (!s || !split)
		return (0);
	i = 0;
	j = 0;
	k = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && k < 0)
			k = i;
		else if ((s[i] == c || i == ft_strlen(s)) && k >= 0)
		{
			split[j++] = ft_word(s, k, i);
			if (!split[j - 1])
				free_alocate(split, j--);
			k = -1;
		}
		i++;
	}
	return (end(split, j));
}

void ft_echo(t_mix *data)
{

    int new_line;
    int i;

    new_line = 1;
    i = 1;

    if (data->m_argv[i] && ft_strcmp(data->m_argv[i], "-n") == 0)
    {
        new_line = 0;
        i++;
    }

    while (data->m_argv[i])
    {
        printf("%s", data->m_argv[i]);
        if (data->m_argv[i + 1])
            printf(" ");
        i++;
    }
    if (new_line)
        printf("\n");
}

void ft_cd(t_mix *data)
{
    if (!data->m_argv[1])
    {
        printf("cd: missing argument\n");
        return;
    }

    if (chdir(data->m_argv[1]) != 0)
    {
        perror("cd");
    }
}

void ft_pwd(void)
{
    char *pwd;
    
    pwd = getcwd(NULL, 0);
    if (pwd)
    {
        printf("%s\n", pwd);
        free(pwd);
    }
    else
    {
        perror("pwd");
    }
}

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

void ft_export(t_mix *data)
{
    char **str;
    int i = 1;

    if (!data->m_argv[1])
    {
        printf("export: missing argument\n");
        return;
    }

    while (data->m_argv[i])
    {
        str = ft_split(data->m_argv[i], '=');

        if (str[0] && str[1])
        {
            data->m_env = add_or_update_env(data->m_env, str[0], str[1]);
            if (!data->m_env)
            {
                perror("export");
                return;
            }
        }
        else
        {
            printf("export: invalid argument '%s'\n", data->m_argv[i]);
        }

        for (int j = 0; str[j]; j++)
            free(str[j]);
        free(str);

        i++;
    }
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

void ft_unset(t_mix *data)
{
    int i = 1;

    if (!data->m_argv[1])
    {
        printf("unset: missing argument\n");
        return;
    }

    while (data->m_argv[i])
    {
        data->m_env = remove_env(data->m_env, data->m_argv[i]);
        if (!data->m_env)
        {
            perror("unset");
            return;
        }
        i++;
    }
}

void ft_env(t_mix *data)
{
    int j;

    j =0;
    while (data->m_env[j])
    {
        if (strchr(data->m_env[j], '='))
            printf("%s\n", data->m_env[j]);
        j++;
    }
}

void ft_exit(t_mix *data)
{
    int status = 0;
    if (data->m_argv[1])
    {
        status = atoi(data->m_argv[1]);
    }
    exit(status);
}

void execute_builtin(char **argv, t_mix *data)
{
    if (ft_strcmp(argv[0], "echo") == 0)
        ft_echo(data);
    else if (ft_strcmp(argv[0], "cd") == 0)
        ft_cd(data);
    else if (ft_strcmp(argv[0], "pwd") == 0)
        ft_pwd();
    else if (ft_strcmp(argv[0], "exit") == 0)
        ft_exit(data);
    else if (ft_strcmp(argv[0], "export") == 0)
        ft_export(data);
    else if (ft_strcmp(argv[0], "unset") == 0)
        ft_unset(data);
    else if (ft_strcmp(argv[0], "env") == 0)
        ft_env(data);
    else
        fprintf(stderr, "%s: command not found\n", argv[0]);
}

void prompt(t_mix *data)
{
    char *input;
    char **argv;

    while ((input = readline("Minishell: ")))
    {
        if (*input)
            add_history(input);

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

int main(int argc, char **argv, char **envp)
{
    t_mix data;

    if (argc != 1 || !argv)
        return 1;

    ft_init_mix(&data);
    ft_fill_struct(&data, argc, argv, envp);
    prompt(&data);
    ft_free_env(data.m_env);
    ft_free_env(data.m_argv);
    return 0;
}