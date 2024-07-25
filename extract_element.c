/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:42:48 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/13 19:55:50 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_double_quotes(char *s, int pos, t_mix *data)
{
	int		len;
	char	*result;

	len = 0;
	while (s[pos + len + 1] != '"')
	{
		while (s[pos + len + 1] != '"' && s[pos + len + 1] != '$')
			len++;
		result = ft_substr(s, pos + 1, len);
		pos = pos + len + 1;
		if (s[pos] == '"')
			return (result);
		if (s[pos] == '$')
		{
			result = expand_variable(result, s, pos, data);
			pos += len_literal_word(s, pos + 1);
		}
		len = 0;
	}
	return (result);
}

static char	*add_chunk(char *original, char *chunk)
{
	char	*aux;

	aux = ft_strjoin(original, chunk);
	if (original != NULL)
		free(original);
	if (chunk != NULL)
		free(chunk);
	return (aux);
}

static int	select_and_expand(char **result, char *s, int *pos, t_mix *data)
{
	size_t	len;
	char	*chunk;

	if (s[*pos] == '\'' || s[*pos] == '"')
		len = len_quotes(s, *pos);
	else
		len = len_literal_word(s, *pos);
	if (s[*pos] == '"')
		chunk = expand_double_quotes(s, *pos, data);
	else if (s[*pos] == '$')
		chunk = obtain_variable(s, *pos + 1, data);
	else
		chunk = ft_substr(s, *pos, len);
	*result = add_chunk(*result, chunk);
	if (!(*result))
		return (1);
	if (s[*pos] == '\'' || s[*pos] == '"')
		*pos = *pos + len + 2;
	else if (s[*pos] == '$')
		*pos = *pos + len_literal_word(s, *pos + 1) + 1;
	else
		*pos = *pos + len;
	return (0);
}

int	something_to_add(char *s, int pos)
{
	if (is_space(s[pos]) == 0 && s[pos] != '<' && s[pos] != '>'
		&& s[pos] != '|')
		return (1);
	return (0);
}

char	*extract_element(char *s, int *pos, t_mix *data)
{
	char	*result;

	if (!s)
		return (NULL);
	result = NULL;
	while (s[*pos] == '<' || s[*pos] == '>' || is_space(s[*pos]) == 1)
		(*pos)++;
	while (something_to_add(s, *pos) == 1)
	{
		if (select_and_expand(&result, s, pos, data) != 0)
			return (NULL);
	}
	return (result);
}
