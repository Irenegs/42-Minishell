/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils_locate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:08:50 by pablgarc          #+#    #+#             */
/*   Updated: 2024/12/12 22:35:20 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	something_to_add(char *s, int pos)
{
	if (is_space(s[pos]) == 0 && s[pos] != '<' && s[pos] != '>'
		&& s[pos] != '|')
		return (1);
	return (0);
}

static int	skip_word(char *s, int pos)
{
	int	len;

	len = 0;
	while (s[pos + len] == '<' || s[pos + len] == '>'
		|| is_space(s[pos + len]) == 1)
		len++;
	while (something_to_add(s, pos + len) == 1)
		len += len_literal_word(s, pos + len);
	return (len);
}

int	locate_cmd_position(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] == '<' || s[i] == '>')
			i += skip_word(s, i);
		if (s[i] == '\0')
			return (-1);
		if (is_space(s[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	locate_char_position(char *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	locate_char_position_quotes(char *s, char c)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] == c && quotes == 0)
			return (i);
		if (s[i] == quotes && quotes != 0)
			quotes = 0;
		else if (quotes == 0 && (s[i] == '\'' || s[i] == '"'))
			quotes = s[i];
		i++;
	}
	return (-1);
}
