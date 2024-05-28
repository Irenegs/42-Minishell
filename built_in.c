/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:31:25 by pablo             #+#    #+#             */
/*   Updated: 2024/05/28 22:05:33 by pablo            ###   ########.fr       */
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
	while (envp[i])
	{
		env_copy
        [i] = strdup(envp[i]);
		i++;
	}
	env_copy
    [i] = NULL;
	return (env_copy);
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
            perror("Error en el duplicado de cadena");
            j = 0;
            while (j < i)
            {
                free(new_argv[j]);
                j++;
            }
            free(new_argv);
            return (NULL);
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

// Función rapida para dividir la entrada en argumentos
char **parse_input(char *input) 
{
    char **c_argv; 
    char **temp;
    int i;
    int	j;

	j = 0;
	i = 0;
	while (input[j])
		j++;
    c_argv = malloc((j + 1) * sizeof(char *));
    if (!c_argv) 
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    temp = ft_split(input, ' ');
    while (temp[i] != NULL && i < (j - 1)) 
    {
        c_argv[i] = temp[i];
        i++;
    }
    c_argv[i] = NULL;
    free (temp);
    return c_argv;
}

void ft_echo(t_mix *data)
{

    int new_line;
    int i;

    new_line = 1;
    i = 1;

    if (data->m_argv[i] && ft_strncmp(data->m_argv[i], "-n", ft_strlen("-n")) == 0)
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
        fprintf(stderr, "cd: missing argument\n");
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

//no se puede usar setenv, tp actualiza bien el entorno, no funciona bien
void ft_export(t_mix *data) 
{
    char **str;
    int i;
    
    i = 1;

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
            if (setenv(str[0], str[1], 1) != 0) 
            {
                perror("export");
            }
        } 
        else 
        {
            printf("export: invalid argument '%s'\n", data->m_argv[i]);
        }

        i++;
    }
    data->m_env = ft_copy_env(data->m_env);
}


void ft_env(t_mix *data) 
{
 int j;

	j = 0;
	while (data->m_env[j])
	{
		if (strchr(data->m_env[j], '='))
			printf("%s\n", data->m_env[j]);
		j++;
	}
}

//no se puede usar unsetenv, no actualiza bien el entorno, no funciona bien
void ft_unset(t_mix *data)
{
    int i;
    
    i = 1;
    if (!data->m_argv[1])
    {
        fprintf(stderr, "unset: missing argument\n");
        return;
    }

    while (data->m_argv[i])
    {
        if (unsetenv(data->m_argv[i]) != 0)
        {
            perror("unset");
        }
        i++;
    }
    data->m_env = ft_copy_env(data->m_env);
}

void ft_exit(t_mix *data)
{
    int status;
    status = 0;
    if (data->m_argv[1])
    {
        status = atoi(data->m_argv[1]); //cambiar por ft_atoi
    }
    exit(status);
}

void execute_builtin(char **argv, t_mix *data)
{
    if (ft_strncmp(argv[0], "echo", ft_strlen("echo")) == 0)
        ft_echo(data);
    else if (ft_strncmp(argv[0], "cd", ft_strlen("cd")) == 0)
        ft_cd(data);
    else if (ft_strncmp(argv[0], "pwd", ft_strlen("pwd")) == 0)
        ft_pwd();
    else if (ft_strncmp(argv[0], "exit", ft_strlen("exit")) == 0)
        ft_exit(data);
    else if (strncmp(argv[0], "export", ft_strlen("export")) == 0)
        ft_export(data);
    else if (strncmp(argv[0], "unset", ft_strlen("unset")) == 0)
        ft_unset(data);
    else if (strncmp(argv[0], "env", ft_strlen("env")) == 0)
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

        argv = parse_input(input);  
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
		return (1);

    ft_init_mix(&data);
    ft_fill_struct(&data, argc, argv, envp);
    prompt(&data);
    return 0;
}