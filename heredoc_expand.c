/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:52:42 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/23 17:05:58 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*normal_expansion(char *orig, char *input_str, int pos, int len)
{
	char	*result;
	char	*chunk;

	chunk = ft_substr(input_str, pos, len);
	if (!chunk)
		return (write_error_null(1));
	result = ft_strjoin(orig, chunk);
	free(orig);
	free(chunk);
	if (!result)
		return (write_error_null(1));
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

	if (!input_str)
		return (NULL);
	expanded = malloc(1 * sizeof(char));
	if (!expanded)
		return (write_error_null(1));
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
			expanded = normal_expansion(expanded, input_str, pos, len_until_dollar(input_str, pos));
			pos += len_until_dollar(input_str, pos);
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
