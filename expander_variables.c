/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:27:26 by irene             #+#    #+#             */
/*   Updated: 2024/12/11 18:20:14 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*variable_escaped_quote(char *str, int pos, t_mix *data)
{
	char	*orig_value;
	char	*escaped_variable;

	orig_value = obtain_variable(str, pos + 1, data);
	if (ft_strrchr(orig_value, '\'') != 0 || ft_strrchr(orig_value, '"') != 0)
	{
		escaped_variable = escape_quotes_in_variable(orig_value);
		free(orig_value);
		return (escaped_variable);
	}
	return (orig_value);
}

static void	add_variable(char **result, char *orig, int pos, t_mix *data)
{
	char	*variable;
	char	*new;

	variable = variable_escaped_quote(orig, pos, data);
	new = ft_strjoin(*result, variable);
	free(variable);
	free(*result);
	*result = new;
}

char	*expand_string(char *str, t_mix *data)
{
	char	*expanded;
	int		pos;
	int		quotes;

	if (!str)
		return (NULL);
	expanded = malloc(1 * sizeof(char));
	if (!expanded)
		return (write_error_null(1));
	expanded[0] = '\0';
	pos = 0;
	quotes = 0;
	while (str[pos] != '\0' && expanded)
	{
		if (str[pos] == '$')
		{
			add_variable(&expanded, str, pos, data);
			pos++;
			pos += len_varname(str, &pos);
			if (str[pos] == '}')
				pos++;
		}
		else if (quotes != 0 && is_quote(str[pos]) == 1 && quotes != str[pos])
		{
			add_escaped_quote(&expanded, str, pos++);
			pos++;
		}
		else
		{
			manage_quotes(&quotes, str[pos]);
			add_char(&expanded, str, pos);
			pos++;
		}
	}
	return (expanded);
}
