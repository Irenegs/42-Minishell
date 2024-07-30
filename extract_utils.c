/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:40:20 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/30 19:25:23 by pablgarc         ###   ########.fr       */
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

int	len_cmd_str(char *str)
{
	int	len;
	int	i;
	int	quotes;

	if (!str)
		return (0);
	len = 1;
	i = 0;
	quotes = 0;
	while (str[i] != '\0' && str[i] != '|')
	{
		i++;
		while (str[i] != '\0' && str[i] != '|' && quotes == 0
			&& (str[i] == '<' || str[i] == '>'))
			i += len_skip_word(str, i);
		manage_quotes(&quotes, str[i]);
		len++;
	}
	return (len);
}
