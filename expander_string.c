/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_string.c       	                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:27:26 by irene             #+#    #+#             */
/*   Updated: 2024/12/12 20:33:55 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!variable)
	{
		free(*result);
		*result = NULL;
		return ;
	}
	new = ft_strjoin(*result, variable);
	if (!new)
		write_error_null(1);
	free(variable);
	free(*result);
	*result = new;
}

static void	dollar_case(char **expanded, char *str, int *pos, t_mix *data)
{
	add_variable(expanded, str, *pos, data);
	(*pos)++;
	(*pos) += len_varname(str, pos);
	if (str[*pos] == '}')
		(*pos)++;
}

static char	*initialize_expand_string(char **expanded, int *pos, int *quotes)
{
	*pos = 0;
	*quotes = 0;
	*expanded = malloc(1 * sizeof(char));
	if (!*expanded)
		return (write_error_null(1));
	*expanded[0] = '\0';
	return (*expanded);
}

char	*expand_string(char *str, t_mix *data)
{
	char	*expanded;
	int		pos;
	int		quotes;

	if (!str)
		return (NULL);
	expanded = initialize_expand_string(&expanded, &pos, &quotes);
	while (expanded && str[pos] != '\0')
	{
		if (str[pos] == '$')
			dollar_case(&expanded, str, &pos, data);
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
