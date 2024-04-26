/*************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:04:13 by irene             #+#    #+#             */
/*   Updated: 2024/04/16 21:58:36 by irene            ###   ########.fr       */
/*                                                                            */
/*************************************************************************** */

#include "minishell.h"

static int	is_space(char c)
{
	if (c == 32 || (c < 14 && c > 8))
		return (1);
	return (0);
}

char obtain_delimiter(char *s, int i)
{
	if (s[i] == '"')
		return('"');
	if (s[i] == '\'')
		return('\'');
	return (' ');
}

int is_metacharacter(char c)
{
	char *metacharacter;
	int i;
	
	metacharacter = "|&;<>()$`\\'\"\n \t";
	i = 0;
	while (metacharacter[i] != '\0')
	{
		if (c == metacharacter[i])
			return (1);
		i++;
	}
	return (0);
}

int is_delimiter(char del, char c)
{
	if (c == '\0')
		return (1);
	if (del == ' ')
		return (is_metacharacter(c));
	return (c == del);
}

char *obtain_word(char *s, int i)
{
	char *s;
	char del;
	int len;
	
	del = obtain_delimiter(s, i);
	if (del = '\'')
	{
		i++;
		len = 0;
		while (is_delimiter(del, s[i + len]) == 0)
			len++;
		if (s[i + len] == '\0')
			return (NULL);
		return(ft_substr(s, i, len));
	}
}

char *obtain_element(char *s, int i)
{
	int len;
	
	len = 0;
	i++;
	while (is_space(s[i]) != 0)
		i++;
	if (s[i] == '|' || s[i] == '<' || s[i] == '>')
	{
		printf("Parse error\n");
		return NULL;
	}
	return (obtain_word(s, i));
}

int redirect_output(char *s, int i)
{
	char *file;
	int len;
	int append;

	append = 0;
	if (s[i + 1] == '\0')
		return (-1);
	if (s[i + 1] == '>')
	{
		append = 1;
		i++;
	}
	file = obtain_element(s, i);
	printf("File %s", file);
	len = ft_strlen(file);
	free(file);
	return (len);
}

int redirect_input(char *s, int i)
{
	char *file;
	int len;

	if (s[i + 1] == '\0')
		return (-1);
	if (s[i + 1] == '<')
	{
		file = obtain_element(s,i + 1);
		free(file);
		return (printf("Delimiter\n"));
	}
	file = obtain_element(s, i);
	printf("File %s", file);
	len = ft_strlen(file);
	free(file);
	return (len);
}

void read_cli(char *s)
{
	int i;
	int len;
	
	i = 0;
	while (is_space(s[i]) == 1)
		i++;
	if (s[i] == '|')
	{
		printf("Parse error near `|\'");
		return ;
	}
	while (s[i] != '\0')
	{
		if (s[i] == '<')
		{
			len = redirect_input(s, i);
			if (len < 1)
				return ;
			i += len;
		}
		if (s[i] == '>')
		{
			len = redirect_output(s, i);
			if (len < 1)
				return ;
			i += len;
		}
		else
			i++;
	}
}

int main(int argc, char **argv)
{
	char 	*s = argv[1];
	
	read_cli(s);
}


/*

COMILLAS
SIN: interpreta todos los metacaracteres:
Metacharacters are: pipe (|), ampersand (&), semicolon (;), less-than sign (<), greater-than sign (>), left parenthesis ((), right parenthesis ()), dollar sign ($), backquote (`), backslash (\), right quote ('), double quotation marks ("), newline character, space character, and tab character.
COMILLA DOBLE: interpreta solo $
COMILLA SIMPLE: no interpreta => tal cual

% echo \"hola$PATH&&echo \$SHELL
"hola/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki
$SHELL
======
% echo "\"hola$PATH&&echo \$SHELL"
"hola/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki&&echo $SHELL
=======
% echo '\"hola$PATH&&echo \$SHELL'
\"hola$PATH&&echo \$SHELL

cuál es el comportamiento exacto de <> 
- obtain word -> comillas
*/







/*
int last_in_words_fun(t_word *words)
{
	t_word *a;

	if (!words)
		return (1);
	a = words;
	while(a && a->next != NULL)
		a = a->next;
	return (a->function);
}

static int calculate_function(char *s, t_word *words)
{
	if (!s)
		return (-1);
	if (*s == '<' && *(s + 1) != '<')
		return (INPUT);
	else if (*s == '<' && *(s + 1) == '<')
		return (DELIMITER);
	else if (*s == '>' && *(s + 1) != '>')
		return (KOUTPUT);
	else if (*s == '>' && *(s + 1) == '>')
		return (OUTPUT);
	else if (last_in_words_fun(words) == COMMAND)
		return (ARG);
	return (COMMAND);
}

static int	calculate_word(char *s, t_word *new)
{
	int j;

	j = 0;
	while (s[j] != ' ' && s[j] != '\0')
		j++;
	new->content = ft_substr(s, 0, j);
	return (j);
}

static int add_words(char *s, t_word *words)
{
	// devuelve lo que se avanza en s al parsear
	int len;
	int fun;
	t_word *new;

	if (!s)
		return (0);
	len = 0;
	new = malloc(sizeof(t_word));
	new->function = calculate_function(s, words);
	len = calculate_word(s, new);
	if (fun == INPUT || fun == DELIMITER)
		ft_lstadd_front(&words, new);
	else
		ft_lstadd_back(&words, new);
	return (len);
}

t_word *parser(char *s)
{
	int i;
	t_word *words;
	int pipes;

	i = 0;
	pipes = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] == '|')
			pipes++;
		i += add_words(s + i, words);
	}
	words = malloc(sizeof(t_word *));
	while(add_words(s, words) != 0)
		i--;
	return (words);
}
*/
/*
1 Delimitar cuántas palabras hay y si es una expresión bien formada. Determinar si hay redirecciones y el número de pipes.
2 Considerar cada palabra con su función. Funciones (input/output_file, comando, argumentos de comando)
*/