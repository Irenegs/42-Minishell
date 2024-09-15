/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:01:32 by irgonzal          #+#    #+#             */
/*   Updated: 2024/09/15 18:13:52 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int  variables_to_expand(char *str)
{
    int quotes;
    int i;
    printf("variables_to_expand\n");
    quotes = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '$' && quotes != '\'')
            return (1);
        i++;
    }
    return (0);
}

static void add_escaped_quote(char *result, char *orig, int pos)
{
    char    *new;
    size_t  len_result;
    
    len_result = ft_strlen(result);
    new = malloc((len_result + 3) * sizeof(char));
    if (!new)
    {
        free(result);
        result = NULL;
        write_error_null(1);
        return ;
    }
    ft_memmove(new, result, len_result);
    new[len_result] = '\\';
    new[len_result + 1] = orig[pos];
    new[len_result + 2] = '\0';
    free(result);
    result = new;
}

static char *escape_variable(char *str)
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
        if (is_quote(str[pos]) == 1)
            add_escaped_quote(escaped, str, pos);
        else
            add_char(&escaped, str, pos);
        pos++;
	}
	return (escaped);
}

static char *variable_escaped_quote(char *str, int pos, t_mix *data)
{
    char    *orig_varvalue;
    char    *escaped_variable;
    
    orig_varvalue = obtain_variable(str, pos + 1, data);
    printf("orig_varvalue:%s\n", orig_varvalue);
    if (ft_strrchr(orig_varvalue, '\'') != 0 || ft_strrchr(orig_varvalue, '"') != 0)
    {
        escaped_variable = escape_variable(orig_varvalue);
        free(orig_varvalue);
        return (escaped_variable);
    }
    return (orig_varvalue);
}

static void add_variable(char **result, char *orig, int pos, t_mix *data)
{
    char    *variable;
    char    *new;

    variable = variable_escaped_quote(orig, pos, data);
    printf("variable:%s\n", variable);
    new = ft_strjoin(*result, variable);
    free(variable);
    free(*result);
    *result = new;
}

char	*expand_str(char *str, t_mix *data)
{
	char	*expanded;
	int		pos;
    int     quotes;

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
            printf("len_varname:%ld\n", len_varname(str, &pos));
            pos += len_varname(str, &pos) + 1;
        }
        else if (quotes != 0 && is_quote(str[pos]) == 1 && quotes != str[pos])
        {
            add_escaped_quote(expanded, str, pos);
            pos++;
        }
        else
        {
            manage_quotes(&quotes, str[pos]);
            add_char(&expanded, str, pos);
            pos++;
        }
        printf("expanded:%s\n", expanded);
        printf("pos:%d\n", pos);
	}
	return (expanded);
}
