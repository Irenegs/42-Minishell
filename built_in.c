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


#define MAX_argv 100  // Número máximo de argumentos
//uso fprintf para probar,habria que hacer una funcion para imprimir en la stderr

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

static int	ft_count_words(const char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (*str)
	{
		if (*str != c && i == 0)
		{
			i = 1;
			count++;
		}
		else if (*str == c)
			i = 0;
		str++;
	}
	return (count);
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

	split = malloc (sizeof(char *) * (ft_count_words (s, c) + 1));
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
    char **argv = malloc(MAX_argv * sizeof(char *));
    char **token;
    int i = 0;

    if (!argv) 
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = ft_split(input, ' ');
    while (token[i] != NULL && i < MAX_argv - 1) 
    {
        argv[i] = token[i];
        i++;
    }
    argv[i] = NULL;
    free (token);
    return argv;
}

void ft_echo(char **argv)
{
    int new_line;
    int i;

    new_line = 1;
    i = 1;

    if (argv[i] && ft_strncmp(argv[i], "-n", ft_strlen("-n")) == 0)
    {
        new_line = 0;
        i++;
    }

    while (argv[i])
    {
        printf("%s", argv[i]);
        if (argv[i + 1])
            printf(" ");
        i++;
    }
    if (new_line)
        printf("\n");
}

void ft_cd(char **argv)
{
    if (!argv[1])
    {
        fprintf(stderr, "cd: missing argument\n");
        return;
    }

    if (chdir(argv[1]) != 0)
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

void ft_export(char **argv) 
{
    char **kv;
    int i;
    i = 1;

    if (!argv[1]) 
    {
        printf("export: missing argument\n");
        return;
    }

    while (argv[i])
     {
        kv = ft_split(argv[i], '=');

        if (kv[0] && kv[1]) 
        {
            if (setenv(kv[0], kv[1], 1) != 0) 
            {
                perror("export");
            }
        } 
        else 
        {
            printf("export: invalid argument '%s'\n", argv[i]);
        }

        i++;
    }
}

//se podra pasar **envp por argumento? Esta funcion solo i que imprime las que he puesto
void ft_env(void) 
{
    const char *env_vars[] = { "PATH", "HOME", "USER", "SHELL", "LANG", "PWD", "LOGNAME", "TERM", NULL};
    const char **var;
    const char *value;
    
    var = env_vars;
    while (*var) 
    {
        value = getenv(*var);
        if (value) 
        {
            printf("%s=%s\n", *var, value);
        }
        var++;
    }
}

void ft_unset(char **argv)
{
    int i;
    i = 1;
    if (!argv[1])
    {
        fprintf(stderr, "unset: missing argument\n");
        return;
    }

    while (argv[i])
    {
        if (unsetenv(argv[i]) != 0)
        {
            perror("unset");
        }
        i++;
    }
}

void ft_exit(char **argv)
{
    int status;
    status = 0;
    if (argv[1])
    {
        status = atoi(argv[1]); //cambiar por ft_atoi
    }
    exit(status);
}

void execute_builtin(char **argv)
{
    if (ft_strncmp(argv[0], "echo", ft_strlen("echo")) == 0)
        ft_echo(argv);
    else if (ft_strncmp(argv[0], "cd", ft_strlen("cd")) == 0)
        ft_cd(argv);
    else if (ft_strncmp(argv[0], "pwd", ft_strlen("pwd")) == 0)
        ft_pwd();
    else if (ft_strncmp(argv[0], "exit", ft_strlen("exit")) == 0)
        ft_exit(argv);
    else if (strncmp(argv[0], "export", ft_strlen("export")) == 0)
        ft_export(argv);
    else if (strncmp(argv[0], "unset", ft_strlen("unset")) == 0)
        ft_unset(argv);
    else if (strncmp(argv[0], "env", ft_strlen("env")) == 0)
        ft_env();
    else
        fprintf(stderr, "%s: command not found\n", argv[0]);
}

void prompt(void)
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
            execute_builtin(argv);
            free(argv);
        }
        free(input);
    }
}

int main(void)
{
    prompt();
    return 0;
}