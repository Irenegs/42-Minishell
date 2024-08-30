/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:23:01 by irgonzal          #+#    #+#             */
/*   Updated: 2024/08/30 20:05:30 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_split_separator(char c, char *sep)
{
	int	i;

	if (sep)
	{
		i = 0;
		while (c != sep[i] && sep[i] != '\0')
			i++;
		if (sep[i] != '\0')
			return (i);
	}
	return (-1);
}

int	is_escaped(char const *s, int i)
{
	if (s[i - 1] == '\\')
		return (1);
	return (0);
}

int	new_word(char const *s, char *sep, int i, int quotes)
{
	if (s && sep)
	{
		if (is_split_separator(s[i], sep) == -1 && quotes == 0)
		{
			if (i == 0)
				return (1);
			if (is_split_separator(s[i - 1], sep) != -1 && is_escaped(s, i - 1) == 0)
				return (1);
		}
		return (0);
	}
	return (1);
}

int	ft_wc(char const *s, char *sep)
{
	int	i;
	int	words;
	int	quotes;

	if (!s)
		return (0);
	i = 0;
	words = 0;
	quotes = 0;
	while (s[i] != '\0')
	{
		if (new_word(s, sep, i, quotes) == 1)
			words += 1;
		if (s[i] == '\'' && is_escaped(s, i) == 0)
			quotes = 1 - quotes;
		i++;
	}
	return (words);
}

int	end_word(char const *s, char *sep, int i, int quot)
{
	if (s && sep && s[i] != '\0')
	{
		if (quot == 1 || is_split_separator(s[i], sep) == -1 || is_escaped(s, i) == 1)
			return (0);
	}
	return (1);
}
