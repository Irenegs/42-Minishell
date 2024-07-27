/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:32:16 by irene             #+#    #+#             */
/*   Updated: 2024/07/27 19:49:26 by irgonzal         ###   ########.fr       */
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

int	parser(char *s)
{
	int	i;
	int	insert[3];
	int	pipes;
	int	quotes;

	i = -1;
	quotes = 0;
	insert[0] = 0;
	insert[1] = 1;
	insert[2] = 1;
	pipes = open_quotes(s);
	while (s[++i] != '\0' && pipes >= 0 && valid_insertion(insert, s[i]) == 1)
	{
		if (quotes == 0)
		{
			if (s[i] == '|')
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
		if (s[i] == quotes && quotes != 0)
			quotes = 0;
		else if (quotes == 0 && (s[i] == '\'' || s[i] == '"'))
			quotes = s[i];
	}
	if (s[i] != '\0')
		return (-1);
	return (pipes);
}
