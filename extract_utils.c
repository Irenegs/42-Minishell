/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:40:20 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/13 19:56:02 by irene            ###   ########.fr       */
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

	len = 0;
	while (s[pos + len] != '\0' && s[pos + len] != '<'
		&& s[pos + len] != '>' && s[pos + len] != '|')
		len++;
	while (is_space(s[pos + len]) == 1 || s[pos + len] == '|'
		|| s[pos + len] == '<' || s[pos + len] == '>')
		len--;
	return (++len);
}
