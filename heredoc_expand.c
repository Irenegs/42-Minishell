/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:52:42 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/12 18:54:04 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*do_expansion(char *original, char *input_str, int pos, int len, t_mix *data)
{
	char	*result;
	char	*chunk;

	if (len == 0)
		chunk = obtain_variable(input_str, pos + 1, data);
	else
		chunk = ft_substr(input_str, pos, len);
	if (!chunk)
		return (NULL);
	result = ft_strjoin(original, chunk);
	free(original);
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
			expanded = do_expansion(expanded, input_str, pos, 0, data);
			pos += len_literal_word(input_str, pos + 1) + 1;
		}
		else
		{
			len = len_until_dollar(input_str, pos);
			expanded = do_expansion(expanded, input_str, pos, len, data);
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
