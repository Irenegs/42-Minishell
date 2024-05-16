/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:32:16 by irene             #+#    #+#             */
/*   Updated: 2024/05/16 22:27:40 by irene            ###   ########.fr       */
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

int valid_insertion(int var[3], char s)
{
	if (s == '|' && var[0] != 1)
		return (0);
	if (s == '<' && var[1] != 1)
		return (0);
	if (s == '>' && var[2] != 1)
		return (0);
	return (1);
}

int is_valid(char s)
{
	if (ft_isalnum(s) == 0 && is_metacharacter(s) == 0)
	{
		if (s != '_' && s != '-' && s != '{' && s != '}')
			return (0);
	}
	return (1);
}

void change_insert(int *var, int pipe, int input, int output)
{
	var[0] = pipe;
	var[1] = input;
	var[2] = output;
}

int redirection(char *s, int i, int insert[3])
{
	if (s[i] != '<' && s[i] != '>')
		return (0);
	if (s[i] == s[i + 1] && s[i] == s[i + 2])
		return (-(i + 3));
	if (valid_insertion(insert, s[i]) != 1)
		return (-(i + 3));	
	if (s[i] == '>')
		change_insert(insert, 0, 0, 1);
	else if (s[i] == '<' && s[i + 1] == '<')
	{
		change_insert(insert, 0, 0, 0);
		return (1);
	}
	if (s[i] == '<')
		change_insert(insert, 0, 0, 1);
	return (0);
}

int	open_quotes(char *s)
{
	int i;
	int quotes;

	i = 0;
	quotes = 0;
	while (s[i] != '\0')
	{
		if (s[i] == quotes && quotes != 0)
			quotes = 0;
		if (quotes == 0 && (s[i] == '\'' || s[i] == '"'))
			quotes = s[i];
		i++;
	}
	if (quotes != 0)
		return (-1);
	return (0);
}

int parser(char *s)
{
	int i;
	int	insert[3];
	int	pipes;

	i = -1;
	insert[0] = 0;
	insert[1] = 1;
	insert[2] = 1;
	pipes = open_quotes(s);
	while (s[++i] != '\0' && is_valid(s[i]) == 1 && pipes >= 0)
	{
		if (s[i] == '|' && valid_insertion(insert, s[i]) == 1)
		{
			pipes++;
			change_insert(insert, 0, 1, 1);
		}
		i += redirection(s, i, insert);
		if (i < 0)
			return (-1);
		if (ft_isalnum(s[i]) == 1)
			change_insert(insert, 1, 1, 1);
	}
	if (s[i] != '\0')
		return (-1);
	return (pipes);
}
