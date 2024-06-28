/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:52:42 by irgonzal          #+#    #+#             */
/*   Updated: 2024/06/28 17:54:08 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_string(char *s)
{
	char	*expanded;
	char	*aux;
	char	*chunk;
	int		pos;
	int		len;

	if (!s)
		return (NULL);
	expanded = NULL;
	pos = 0;
	while (s[pos] != '\0')
	{
		if (s[pos] != '$')
		{
			len = len_literal_word(s, pos);
			chunk = ft_substr(s, pos, len);
			pos = pos + len;
			aux = expanded;
			expanded = ft_strjoin(aux, chunk);
			if (aux)
				free(aux);
			if (chunk)
				free(chunk);
		}
		else
		{
			chunk = obtain_variable(s, pos + 1);
			pos += len_literal_word(s, pos + 1) + 1;
			aux = expanded;
			expanded = ft_strjoin(aux, chunk);
			if (aux)
				free(aux);
		}
	}
	return (expanded);
}

int	must_expand(char *s)
{
	if (!s)
		return (0);
	while (*s != '<' && *s != '\0')
		s++;
	while (*s == '<' || is_space(*s) == 1)
		s++;
	if (*s == '"' || *s == '\'')
		return (0);
	return (1);
}
