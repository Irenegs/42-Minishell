/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:01:32 by irgonzal          #+#    #+#             */
/*   Updated: 2024/08/30 20:15:41 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *extract_str_element(char *s, int pos)
{
    int     len;
    int     quotes;
    char    *result;

    if (!s)
        return (NULL);
    len = 0;
    quotes = 0;
    while (s[len] != '\0' && (quotes != 0 || is_separator(s[len]) != 0))
    {
        manage_quotes(&quotes, s[len]);
        len++;
    }
    result = ft_substr(s, pos, len);
    if (!result)
        return (write_error_null(1));
    return (result);
}

int spaces_in_variable(char *str, int pos, t_mix *data)
{
    char    *var_value;
    int     i;
    int     spaces;
    
    var_value = obtain_variable(str, pos, data);
    if (!var_value)
        return (-1);//y si no existe la variable?
    i = 0;
    spaces = 0;
    while (var_value[i] != '\0')
    {
        if (is_space(var_value[i]) != 0 && is_space(var_value[i + 1]) == 0)
            spaces++;
        i++;
    }
    printf("var_value:%s*\n", var_value);
    printf("spaces %d\n", spaces);
    free(var_value);
    return (spaces);
}

int count_elements(char *str, t_mix *data)
{
    int n;
    int i;
    int quotes;
    int spaces;

    if (!str)
        return (0);
    n = 1;
    i = 0;
    quotes = 0;
    while (str[i] != '\0')
    {
        if (quotes == 0 && str[i] == '$')
        {
            spaces = spaces_in_variable(str, i, data);
            if (spaces == -1)
                return (-1);
            n += spaces;
        }
        manage_quotes(&quotes, str[i]);
        i++;
    }
    return (n);
}

char    **extract_element(char *s, int pos, t_mix *data)
{
    char    *str;
    int     n_elem;
    
    if (!data)
        printf("No data\n");
    str = extract_str_element(s, pos);
    n_elem = count_elements(str, data);
    printf("string:%s\n", str);
    printf("Count:%d\n", n_elem);
    free(str);
    return (NULL);
}
