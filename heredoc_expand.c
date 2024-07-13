/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:52:42 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/12 20:32:57 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*normal_expansion(char *orig, char *input_str, int pos, int len)
{
	char	*result;
	char	*chunk;

	chunk = ft_substr(input_str, pos, len);
	if (!chunk)
		return (NULL);
	result = ft_strjoin(orig, chunk);
	free(orig);
	free(chunk);
	return (result);
}

static int	len_until_dollar(char *str, int pos)
{
	int	len;

	len = 0;
	if (!str)
		return (-1);
	while (str[pos + len] != '\0' && str[pos + len] != '$')
		len++;
	return (len);
}

char	*expand_string(char *input_str, t_mix *data)
{
	char	*expanded;
	int		pos;
	int		len;

	if (!input_str)
		return (NULL);
	expanded = malloc(1 * sizeof(char));
	expanded[0] = '\0';
	pos = 0;
	while (input_str[pos] != '\0' && expanded)
	{
		if (input_str[pos] == '$')
		{
			expanded = expand_variable(expanded, input_str, pos, data);
			pos += len_literal_word(input_str, pos + 1) + 1;
		}
		else
		{
			len = len_until_dollar(input_str, pos);
			expanded = normal_expansion(expanded, input_str, pos, len);
			pos = pos + len;
		}
	}
	return (expanded);
}

int	must_expand(char *delimiter, char *text)
{
	if (!delimiter || !text)
		return (0);
	if (ft_strchr(text, '$') == 0)
		return (0);
	while (*delimiter != '<' && *delimiter != '\0')
		delimiter++;
	while (*delimiter == '<' || is_space(*delimiter) == 1)
		delimiter++;
	if (*delimiter == '"' || *delimiter == '\'')
		return (0);
	return (1);
}
