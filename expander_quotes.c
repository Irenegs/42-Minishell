/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:53:19 by irene             #+#    #+#             */
/*   Updated: 2024/12/12 20:34:04 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*unquote_str(char *str)
{
	int		i;
	char	*unquoted;

	if (!str)
		return (NULL);
	unquoted = malloc(1 * sizeof(char));
	if (!unquoted)
	{
		free(str);
		return (write_error_null(1));
	}
	unquoted[0] = '\0';
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '\\' && is_quote(str[i + 1]) != 0)
		{
			add_char(&unquoted, str, i + 1);
			i++;
		}
		else if (is_quote(str[i]) == 0)
			add_char(&unquoted, str, i);
	}
	free(str);
	return (unquoted);
}

static int	quote_in_element(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (is_quote(str[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

char	**unquote(char **element)
{
	int	n;

	n = 0;
	while (element[n])
	{
		if (quote_in_element(element[n]) == 1)
		{
			element[n] = unquote_str(element[n]);
			if (!element[n])
			{
				ft_out_exception(element, n);
				return (NULL);
			}
		}
		n++;
	}
	return (element);
}

void	add_escaped_quote(char **result, char *orig, int pos)
{
	char	*new;
	size_t	len_result;

	len_result = ft_strlen(*result);
	new = malloc((len_result + 3) * sizeof(char));
	if (!new)
	{
		free(*result);
		*result = NULL;
		write_error_null(1);
		return ;
	}
	ft_memmove(new, *result, len_result);
	new[len_result] = '\\';
	new[len_result + 1] = orig[pos];
	new[len_result + 2] = '\0';
	free(*result);
	*result = new;
}

char	*escape_quotes_in_variable(char *str)
{
	char	*escaped;
	int		pos;

	if (!str)
		return (NULL);
	escaped = malloc(1 * sizeof(char));
	if (!escaped)
		return (write_error_null(1));
	escaped[0] = '\0';
	pos = 0;
	while (str[pos] != '\0' && escaped)
	{
		if (is_quote(str[pos]) != 0)
			add_escaped_quote(&escaped, str, pos);
		else
			add_char(&escaped, str, pos);
		pos++;
	}
	return (escaped);
}
