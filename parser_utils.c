/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:29:21 by irene             #+#    #+#             */
/*   Updated: 2024/11/24 18:53:54 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	parsing_without_quotes(char *s, int pos, int insert[3])
{
	if (s[pos] == '|')
		change_insert(insert, 0, 1, 1);
	pos += redirection(s, pos, insert);
	if (pos < 0)
		return (-1);
	if (ft_isalnum(s[pos]) == 1)
		change_insert(insert, 1, 1, 1);
	return (pos);
}

int	parser_errors(char *s)
{
	int	i;
	int	insert[3];

	i = -1;
	change_insert(insert, 0, 1, 1);
	while (i != -1 && s[++i] != '\0' && valid_insertion(insert, s[i]) == 1)
	{
		if (s[i] != '\'' && s[i] != '"')
			i = parsing_without_quotes(s, i, insert);
		else
		{
			i = parser_manage_quotes(s, i);
			change_insert(insert, 1, 1, 1);
		}
	}
	if (i == -1 || s[i] != '\0' || valid_insertion(insert, '|') != 1)
		return (-1);
	return (0);
}
