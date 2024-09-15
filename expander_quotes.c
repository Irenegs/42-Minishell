/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:53:19 by irene             #+#    #+#             */
/*   Updated: 2024/09/15 17:54:19 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char    *unquote_str(char *str)
{
    int     i;
    char    *unquoted;
    printf("unquote_str\n");
    i = 0;
	if (!str)
		return (NULL);
	unquoted = malloc(1 * sizeof(char));
	if (!unquoted)
		return (write_error_null(1));
	unquoted[0] = '\0';
    while (str[i] != '\0')
    {
        if (str[i] == '\\' && is_quote(str[i + 1]) != 0)
        {
            add_char(&unquoted, str, i + 1);
            i++;
        }
        else if (is_quote(str[i]) == 0)
            add_char(&unquoted, str, i);
        i++;
    }
    free(str);
    return (unquoted);
}

static int quote_in_element(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (is_quote(str[i]) != 0)
            return (1);
        i++;
    }
    return (0);
}

char    **unquote(char **element)
{
    int n;
    printf("unquote\n");
    n = 0;
    while (element[n])
    {
        if (quote_in_element(element[n]) == 1)
        {
            element[n] = unquote_str(element[n]);
            if (!element[n])
            {
                ft_out(element);//hay que liberar también los posteriores...
                return (NULL);
            }
        }
        n++;
    }
    return (element);
}
