/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:42:48 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/12 18:53:09 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *var_name, t_mix *data)
{
	int	var_number;

	if (ft_strncmp(var_name, "?", 1) == 0)
		return(ft_itoa(data->exit_status));
	var_number = select_variable(var_name, data->m_env);
	if (var_number < 0)
		return (NULL);
	return (ft_substr(data->m_env[var_number], ft_strlen(var_name) + 1, ft_strlen(data->m_env[var_number]) - ft_strlen(var_name) - 1));
}

char	*obtain_variable(char *s, int i, t_mix *data)
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
	var_value = ft_getenv(var_name, data);
	free(var_name);
	return (var_value);
}

static char	*expand_double_quotes(char *s, int pos, t_mix *data)
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
			chunk = obtain_variable(s, pos + 1, data);
			pos += len_literal_word(s, pos + 1);
			aux = result;
			result = ft_strjoin(aux, chunk);
			if (chunk)
				free(chunk);
			free(aux);
		}
		len = 0;
	}
	return (result);
}

static char	*add_chunk(char *original, char *input, int pos, int len, t_mix *data)
{
	char	*chunk;
	char	*aux;

	if (len > 0)
		chunk = ft_substr(input, pos, len);
	else if (len == 0)
		chunk = expand_double_quotes(input, pos, data);
	else
		chunk = obtain_variable(input, pos + 1, data);
	aux = original;
	original = ft_strjoin(aux, chunk);
	free(aux);
	if (chunk != NULL)
		free(chunk);
	return (original);
}

static int	function(char **result, char *s, int *pos, t_mix *data)
{
	size_t	len;

	if (s[*pos] == '\'' || s[*pos] == '"')
	{
		len = len_quotes(s, *pos);
		if (s[*pos] == '\'')
			*result = add_chunk(*result, s, *pos + 1, len, data);
		else
			*result = add_chunk(*result, s, *pos, 0, data);
		*pos = *pos + len + 2;
	}
	else if (s[*pos] == '$')
	{
		*result = add_chunk(*result, s, *pos, -1, data);
		*pos += len_literal_word(s, *pos + 1) + 1;
	}
	else
	{
		len = len_literal_word(s, *pos);
		*result = add_chunk(*result, s, *pos, len, data);
		*pos = *pos + len;
	}
	if (!(*result))
		return (1);
	return (0);
}

char	*extract_element(char *s, int pos, t_mix *data)
{
	char	*result;

	if (!s)
		return (NULL);
	result = NULL;
	while (s[pos] == '<' || s[pos] == '>' || is_space(s[pos]) == 1)
		pos++;
	while (something_to_add(s, pos) == 1)
	{
		if (function(&result, s, &pos, data) != 0)
			return (NULL);
	}
	return (result);
}
