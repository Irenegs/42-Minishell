/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:56:15 by irene             #+#    #+#             */
/*   Updated: 2024/11/24 00:05:35 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *escape_quotes_in_string(char *str)
{
    char	*escaped;
	int		pos;
    int     quot;

	if (!str)
		return (NULL);
	escaped = malloc(1 * sizeof(char));
	if (!escaped)
		return (write_error_null(1));
	escaped[0] = '\0';
    quot = 0;
	pos = 0;
	while (str[pos] != '\0' && escaped)
	{
        if (is_quote(str[pos]) != 0 && quot != 0 && quot != is_quote(str[pos]))//&& is_escaped(str, pos) == 0)
            add_escaped_quote(&escaped, str, pos);
        else
        {
            if (is_quote(str[pos]) != 0 && is_escaped(str, pos) == 0)
                manage_quotes(&quot, str[pos]);
            add_char(&escaped, str, pos);
        }
        pos++;
	}
	return (escaped);
}

static int  variables_to_expand(char *str)
{
    int quotes;
    int i;

    quotes = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '$' && quotes != '\'')
            return (1);
        manage_quotes(&quotes, str[i]);
        i++;
    }
    return (0);
}

static char *extract_str_element(char *s, int pos)
{
    int     len;
    int     q;
    char    *result;

    if (!s)
        return (NULL);
    len = 0;
    q = 0;
    while(s[pos + len] == ' ')
        pos++;
    while (s[pos + len] != '\0' && (q != 0 || is_separator(s[pos + len]) != 0))
    {
        manage_quotes(&q, s[pos + len]);
        len++;
    }
    result = ft_substr(s, pos, len);
    if (!result)
        return (write_error_null(1));
    return (result);
}

char    **escape_quotes_in_array(char **array)
{
    char    *aux_str;
    int     i;

    i = 0;
    while (array && array[i])
    {
        aux_str = escape_quotes_in_string(array[i]);
        free(array[i]);
        array[i] = aux_str;
        i++;
    }
    return (array);
}

char    **extract_element(char *s, int pos, t_mix *data)
{
    char    *str;
    char    *aux_str;
    char    **element;

    str = extract_str_element(s, pos);
    if (!str)
        return(NULL);
    if (variables_to_expand(str) == 1)
    {
        aux_str = expand_string(str, data);
        if (!aux_str) 
        {
            free(str);
            return (NULL);
        }
        free(str);
        str = aux_str;    
    }
    element = split_element(str);
	free(str);
    element = escape_quotes_in_array(element);
    if (!element)
        return (NULL);
    unquote(element);
    return (element);
}
