/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:40:20 by irgonzal          #+#    #+#             */
/*   Updated: 2024/12/11 23:43:44 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	len_literal_word(char *s, int pos)
{
	size_t	len;

	len = 1;
	while (s[pos + len] != '\'' && s[pos + len] != '"' && s[pos + len] != '$'
		&& is_space(s[pos + len]) == 0 && s[pos + len] != '\0')
		len++;
	return (len);
}

size_t	len_quotes(char *s, int pos)
{
	size_t	len;
	char	quote;

	len = 0;
	quote = s[pos];
	while (s[pos + 1 + len] != '\0' && s[pos + 1 + len] != quote)
	{
		len++;
	}
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
	while (str[i] != '\0' && (str[i] != '|' || quotes != 0))
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
