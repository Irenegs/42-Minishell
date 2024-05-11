/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:44:45 by irgonzal          #+#    #+#             */
/*   Updated: 2024/05/11 17:42:55 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int is_metacharacter(char c)
{
	char *metacharacter;
	int i;
	
	metacharacter = "|$<>'\"\n \t";
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

int obtain_len(char *s, int i, char del)
{
	int len;
	
	len = 0;
	while (is_delimiter(del, s[i + len]) == 0)
		len++;
	return (len);
}

char *obtain_word(char *s, int i, char del)
{
	int len;

	len = obtain_len(s, i, del);
	if (len == 0)
		return (NULL);
	return(ft_substr(s, i, len));
}

int	obtain_variables_to_expand(char *s, int i, char del)
{
	int		var;
	
	var = 0;
	while (is_delimiter(del, s[i]) == 0 || s[i] == '$')
	{
		if (s[i] == '$')
			var++;
		i++;
	}
	return (var);
}

char *obtain_variable(char *s, int i)
{
	char *var_name;
	char *var_value;

	var_name = obtain_word(s, i + 1, ' ');
	var_value = getenv(var_name);
	if (var_value == 0)
		return (NULL);
	return (var_value);
}

char *obtain_element(char *s, int i)
{
	int len;
	
	len = 0;
	while (is_space(s[i]) != 0)
		i++;
	if (s[i] == '|' || s[i] == '<' || s[i] == '>')
	{
		printf("Parse error_%d_%c*\n", s[i], i);
		return NULL;
	}
	if (s[i] == '\'')
		return (obtain_word(s, i + 1, '\''));
	if (s[i] == '"')
		return (expand_string(s, i + 1, '"'));
	return (expand_string(s, i, ' '));
}

/*
int redirect_output(char *s, int i)
{
	char *file;
	int len;
	int append;

	append = 0;
	if (s[i + 1] == '\0')
		return (-1);
	len = 1;
	if (s[i + len] == '>')
	{
		append = 1;
		len++;
	}
	while (is_space(s[i + len]) == 1)
		len++;
	file = obtain_element(s, i);
	printf("Output: %s\n", file);
	len += ft_strlen(file);
	free(file);
	return (len);
}

int redirect_input(char *s, int i)
{
	char *file;
	int len;

	if (s[i + 1] == '\0')
		return (-1);
	len = 1;
	if (s[i + len] == '<')
	{
		len++;
		while (is_space(s[i + len]) == 1)
			len++;
		file = obtain_element(s,i + len);
		free(file);
		return (printf("Delimiter\n"));
	}
	while (is_space(s[i + len]) == 1)
		len++;
	printf("Input len: %d\n", len);
	file = obtain_element(s, i + len - 1);
	printf("Input: %s\n", file);
	len += ft_strlen(file);
	printf("Input len: %d\n", len);
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
		printf("Bucleando %d\n", i);
		while (is_space(s[i]) == 1)
			i++;
		if (s[i] == '<')
		{
			printf("i %d\n", i);
			len = redirect_input(s, i);
			if (len < 1)
				return ;
			i += len;
		}
		else if (s[i] == '>')
		{
			len = redirect_output(s, i);
			if (len < 1)
				return ;
			i += len;
		}
		else
		{
			while (is_space(s[i]) == 1)
				i++;
			char *element = obtain_element(s, i);
			if (!element)
				exit(0);
			printf("Element: %s\n", element);
			len = ft_strlen(element);
			if (len < 1)
				return ;
			i += len;
			free(element);
		}
	}
}

int main(int argc, char **argv)
{
	char 	*s = argv[1];
	
	read_cli(s);
}
*/

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
1 Delimitar cuántas palabras hay y si es una expresión bien formada. Determinar si hay redirecciones y el número de pipes.
2 Considerar cada palabra con su función. Funciones (input/output_file, comando, argumentos de comando)
*/