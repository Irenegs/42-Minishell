/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:40:20 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/27 19:57:27 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	if (c == 32 || (c < 14 && c > 8) || c == '\0')
		return (1);
	return (0);
}

size_t	len_literal_word(char *s, int pos)
{
	size_t	len;

	len = 1;
	while (s[pos + len] != '\'' && s[pos + len] != '"' && s[pos + len] != '$'
		&& is_space(s[pos + len]) == 0 && s[pos + len] != '\0')
		len++;
	return (len);
}

size_t	len_delimiter(char *s, int pos)
{
	size_t	len;

	len = 1;
	if (s[pos] == '\'' || s[pos] == '"')
	{
		len = 1;
		while (s[pos + len] != '\0' && s[pos + len] != s[pos])
			len++;
	}
	else
	{
		while (s[pos + len] != '\0' && s[pos + len] != '<'
			&& s[pos + len] != '>' && s[pos + len] != '\''
			&& s[pos + len] != '"' && is_space(s[pos + len]) == 0 && len < 10)
			len++;
	}
	return (len);
}

size_t	len_quotes(char *s, int pos)
{
	size_t	len;

	len = 0;
	while (s[pos + 1 + len] != '\0' && s[pos + 1 + len] != s[pos])
		len++;
	return (len);
}

int	len_cmd(char *s, int pos)
{
	int	len;
	int	quotes;

	len = 0;
	quotes = 0;
	while (s[pos + len] != '\0')
	{ 
		if (quotes == 0)
		{
			if (s[pos + len] == '<' || s[pos + len] == '>' || s[pos + len] == '|')
				break;
		}
		if (s[pos + len] == quotes && quotes != 0)
			quotes = 0;
		else if (quotes == 0 && (s[pos + len] == '\'' || s[pos + len] == '"'))
			quotes = s[pos + len];
		len++;
	}
	while (is_space(s[pos + len]) == 1 || s[pos + len] == '|'
		|| s[pos + len] == '<' || s[pos + len] == '>')
		len--;
	return (++len);
}
