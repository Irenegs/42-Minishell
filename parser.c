/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:32:16 by irene             #+#    #+#             */
/*   Updated: 2024/11/24 18:48:37 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser_manage_quotes(char *s, int pos)
{
	int	quote;

	quote = s[pos];
	pos++;
	while (s[pos] != '\0' && s[pos] != quote)
		pos++;
	return (pos);
}

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
		i = parser_manage_quotes(s, i);
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

int	parser(char *s)
{
	if (white_string(s) == 1)
		return (-2);
	if (open_quotes(s) == -1 || parser_errors(s) == -1)
		return (-1);
	return (count_pipes(s));
}
