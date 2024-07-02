/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:42:48 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/02 19:30:19 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*obtain_variable(char *s, int i)
{
	char	*var_name;
	char	*var_value;
	size_t	len;

	len = len_literal_word(s, i);
	if (len > 0 && s[i] == '{')
		var_name = ft_substr(s, i + 1, len - 2);
	else
		var_name = ft_substr(s, i, len);
	if (!var_name)
		return (NULL);
	var_value = getenv(var_name);
	free(var_name);
	return (var_value);
}

static char	*expand_double_quotes(char *s, int pos)
{
	int		len;
	char	*result;
	char	*aux;
	char	*chunk;

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
			chunk = obtain_variable(s, pos + 1);
			pos += len_literal_word(s, pos + 1);
			aux = result;
			result = ft_strjoin(aux, chunk);
			free(aux);
		}
		len = 0;
	}
	return (result);
}

char	*add_chunk(char *original, char *input, int pos, int len)
{
	char	*chunk;
	char	*aux;

	if (len > 0)
		chunk = ft_substr(input, pos, len);
	else if (len == 0)
		chunk = expand_double_quotes(input, pos);
	else
		chunk = obtain_variable(input, pos + 1);
	aux = original;
	original = ft_strjoin(aux, chunk);
	free(aux);
	if (len >= 0)
		free(chunk);
	return (original);
}

char	*extract_element(char *s, int pos)
{
	size_t	len;
	char	*result;

	if (!s)
		return (NULL);
	result = NULL;
	while (s[pos] == '<' || s[pos] == '>' || is_space(s[pos]) == 1)
		pos++;
	while (something_to_add(s, pos) == 1)
	{
		if (s[pos] == '\'' || s[pos] == '"')
		{
			len = len_quotes(s, pos);
			if (s[pos] == '\'')
				result = add_chunk(result, s, pos + 1, len);
			else
				result = add_chunk(result, s, pos, 0);
			pos = pos + len + 2;
		}
		else if (s[pos] == '$')
		{
			result = add_chunk(result, s, pos, -1);
			pos += len_literal_word(s, pos + 1) + 1;
		}
		else
		{
			len = len_literal_word(s, pos);
			result = add_chunk(result, s, pos, len);
			pos = pos + len;
		}
	}
	return (result);
}
