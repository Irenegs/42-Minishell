/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:32:16 by irene             #+#    #+#             */
/*   Updated: 2024/08/26 19:37:36 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_quotes(char *s)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (s[i] != '\0')
	{
		if (s[i] == quotes && quotes != 0)
			quotes = 0;
		else if (quotes == 0 && (s[i] == '\'' || s[i] == '"'))
			quotes = s[i];
		i++;
	}
	if (quotes != 0)
		return (-1);
	return (0);
}

int	parser_manage_quotes(char *s, int pos, int quotes)
{
	if (s[pos] == quotes && quotes != 0)
		quotes = 0;
	else if (quotes == 0 && (s[pos] == '\'' || s[pos] == '"'))
		quotes = s[pos];
	while (quotes != 0 && s[pos] != quotes)
		pos++;
	return (pos);
}

int	count_pipes(char *s)
{
	int	i;
	int	pipes;
	int	quotes;

	i = -1;
	quotes = 0;
	pipes = 0;
	while (s[++i] != '\0' && pipes >= 0)
	{
		if (quotes == 0 && s[i] == '|')
		{
			pipes++;
			i++;
		}
		i = parser_manage_quotes(s, i, quotes);
	}
	return (pipes);
}

int	white_string(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (is_space(s[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

static int	valid_insertion(int var[3], char c)
{
	if (c == '|' && var[0] != 1)
		return (0);
	if (c == '<' && var[1] != 1)
		return (0);
	if (c == '>' && var[2] != 1)
		return (0);
	return (1);
}

static void	change_insert(int *var, int pipe, int input, int output)
{
	var[0] = pipe;
	var[1] = input;
	var[2] = output;
}

static int	redirection(char *s, int i, int insert[3])
{
	if (s[i] != '<' && s[i] != '>')
		return (0);
	if (s[i] == s[i + 1] && s[i] == s[i + 2])
		return (-(i + 3));
	if (valid_insertion(insert, s[i]) != 1)
		return (-(i + 3));
	if (s[i] == '>')
		change_insert(insert, 0, 0, 1);
	else if (s[i] == '<')
	{
		change_insert(insert, 0, 0, 0);
		if (s[i + 1] == '<')
			return (1);
	}
	return (0);
}

int	parser_errors(char *s)
{
	int	i;
	int	insert[3];
	int	quotes;

	i = -1;
	quotes = 0;
	insert[0] = 0;
	insert[1] = 1;
	insert[2] = 1;
	while (s[++i] != '\0' && valid_insertion(insert, s[i]) == 1)
	{
		if (quotes == 0 && s[i] != '\'' && s[i] != '"')
		{
			if (s[i] == '|')
				change_insert(insert, 0, 1, 1);
			i += redirection(s, i, insert);
			if (i < 0)
				return (-1);
			if (ft_isalnum(s[i]) == 1)
				change_insert(insert, 1, 1, 1);
		}
		i = parser_manage_quotes(s, i, quotes);
	}
	if (s[i] != '\0' || valid_insertion(insert, '|') != 1)
		return (-1);
	return (0);
}

int	parser(char *s)
{
	if (white_string(s) == 1)
		return (-2);
	if (open_quotes(s) == -1 || parser_errors(s) == -1)
		return (-1);
	return (count_pipes(s));
}
