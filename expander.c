/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:56:15 by irene             #+#    #+#             */
/*   Updated: 2024/10/25 18:52:18 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  variables_to_expand(char *str)
{
    int quotes;
    int i;
    printf("==variables_to_expand==\n");
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
    int     quotes;
    char    *result;

    if (!s)
        return (NULL);
    len = 0;
    quotes = 0;
    while (s[pos + len] != '\0' && (quotes != 0 || is_separator(s[pos + len]) != 0))
    {
        manage_quotes(&quotes, s[pos + len]);
        len++;
    }
    result = ft_substr(s, pos, len);
    if (!result)
        return (write_error_null(1));
    return (result);
}

char    **extract_element(char *s, int pos, t_mix *data)
{
    char    *str;
    char    *aux_str;
    char    **element;

    str = extract_str_element(s, pos);
    printf("extract_str_element:%s\n", str);
    if (variables_to_expand(str) == 1)
    {
        aux_str = expand_string(str, data);
        free(str);
        str = aux_str;    
    }
    element = split_element(str);
	free(str);
    unquote(element);
    return (element);
}
