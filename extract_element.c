/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:42:48 by irgonzal          #+#    #+#             */
/*   Updated: 2024/05/19 19:16:00 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *obtain_variable(char *s, int i)
{
	//TODO Falta gestionar $? 
	char *var_name;
	char *var_value;
	size_t len;

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
	while(s[pos + len + 1] != '"')
	{
		while(s[pos + len + 1] != '"' && s[pos + len + 1] != '$')
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

char *extract_element(char *s, int pos)
{
	//TODO proteger frees cuando algo es NULL
	size_t	len;
	char	*result;
	char	*chunk;
	char	*aux;

	if (!s)
		return (NULL);
	result = NULL;
	while (s[pos] == '<' || s[pos] == '>' || is_space(s[pos]) == 1)
		pos++;
	while (something_to_add(s, pos) == 1)
	{
		if (s[pos] == '\'')
		{
			len = len_quotes(s, pos);
			chunk = ft_substr(s, pos + 1, len);
			pos = pos + len + 2;
			aux = result;
			result = ft_strjoin(aux, chunk);
			free(aux);
			free(chunk);
		}
		else if (s[pos] == '"')
		{
			chunk = expand_double_quotes(s, pos);
			pos += len_quotes(s, pos) + 2;
			aux = result;
			result = ft_strjoin(aux, chunk);
			free(aux);
			free(chunk);
		}
		else if (s[pos] == '$')
		{
			chunk = obtain_variable(s, pos + 1);
			pos += len_literal_word(s, pos + 1) + 1;
			aux = result;
			result = ft_strjoin(aux, chunk);
			free(aux);
		}
		else
		{
			len = len_literal_word(s, pos);
			chunk = ft_substr(s, pos, len);
			pos = pos + len;
			aux = result;
			result = ft_strjoin(aux, chunk);
			free(aux);
			free(chunk);
		}
	}
	return (result);
}

