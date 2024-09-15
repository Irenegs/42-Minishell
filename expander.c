/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:56:15 by irene             #+#    #+#             */
/*   Updated: 2024/09/15 18:28:11 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    char    **unquoted_element;

    str = extract_str_element(s, pos);
    printf("extract_str_element:%s\n", str);
    if (variables_to_expand(str) == 1)
    {
        printf("hay variables a expandir\n");
        aux_str = expand_str(str, data);
        free(str);
        str = aux_str;    
    }
    element = ft_split(str, ' ');//cambiar split para  ambos tipos de comillas
	free(str);
    unquoted_element = unquote(element);
    free(element);
    return (unquoted_element);
}
