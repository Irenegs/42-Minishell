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
	return (words);
}

/*
1 Delimitar cuántas palabras hay y si es una expresión bien formada. Determinar si hay redirecciones y el número de pipes.
2 Considerar cada palabra con su función. Funciones (input/output_file, comando, argumentos de comando)
*/