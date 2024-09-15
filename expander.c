/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:01:32 by irgonzal          #+#    #+#             */
/*   Updated: 2024/09/15 16:48:16 by irene            ###   ########.fr       */
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

static int  variables_to_expand(char *str)
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
    printf("varialbes to expand = 0\n");
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

static void add_char(char *result, char *orig, int pos)
{
    char    *new;
    size_t  len_result;
    
    len_result = ft_strlen(result);
    new = malloc((len_result + 2) * sizeof(char));
    if (!new)
    {
        free(result);
        result = NULL;
        write_error_null(1);
        return ;
    }
    ft_memmove(new, result, len_result);
    new[len_result] = orig[pos];
    new[len_result + 1] = '\0';
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
            add_char(escaped, str, pos);
        pos++;
	}
	return (escaped);
}

static char *variable_escaped_quote(char *str, int pos, t_mix *data)
{
    char    *orig_varvalue;
    char    *escaped_variable;
    
    orig_varvalue = obtain_variable(str, pos + 1, data);
    if (ft_strrchr(orig_varvalue, '\'') != 0 || ft_strrchr(orig_varvalue, '"') != 0)
    {
        escaped_variable = escape_variable(orig_varvalue);
        free(orig_varvalue);
        return (escaped_variable);
    }
    return (orig_varvalue);
}

static void add_variable(char *result, char *orig, int pos, t_mix *data)
{
    char    *variable;
    char    *new;

    variable = variable_escaped_quote(orig, pos, data);
    new = ft_strjoin(result, variable);
    free(variable);
    free(result);
    result = new;
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
            add_variable(expanded, str, pos, data);
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
            add_char(expanded, str, pos);
            pos++;
        }
	}
	return (expanded);
}

static char    *unquote_str(char *str)
{
    int     i;
    char    *unquoted;

    i = 0;
	if (!str)
		return (NULL);
	unquoted = malloc(1 * sizeof(char));
	if (!unquoted)
		return (write_error_null(1));
	unquoted[0] = '\0';
    while (str[i] != '\0')
    {
        if (str[i] == '\'' && is_quote(str[i + 1]))
        {
            add_char(unquoted, str, i + 1);
            i++;
        }
        else if (is_quote(str[i]) == 0)
            add_char(unquoted, str, i);
        i++;
    }
    printf("unquoted:%s\n", unquoted);
    return (unquoted);
}

static char    **unquote(char **element)
{
    int n;
    printf("unquote\n");
    n = 0;
    while (element[n])
    {
        element[n] = unquote_str(element[n]);
        if (!element[n])
        {
            ft_out(element);//hay que liberar también los posteriores...
            return (NULL);
        }
        n++;
    }
    return (element);
}

char    **extract_element(char *s, int pos, t_mix *data)
{
    char    *str;
    char    *aux_str;
    char    **element;
    char    **unquoted_element;
    printf("extract_element\n");
    str = extract_str_element(s, pos);
    printf("extract_str_element:%s\n", str);
    if (variables_to_expand(str) == 1)
    {
        printf("hay variables a expandir\n");
        aux_str = expand_str(str, data);
        free(str);
        str = aux_str;    
    }
    element = ft_split(str, ' ');//cambiar super split para gestionar ambos tipos de comillas?
    free(str);
    printf("element[0]:%s\n", element[0]);
    unquoted_element = unquote(element);
    printf("despues unquote\n");
    //ft_out(element);
    printf("deps ft_out\n");
    return (unquoted_element);
}
