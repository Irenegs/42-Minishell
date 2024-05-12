/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:36:46 by irgonzal          #+#    #+#             */
/*   Updated: 2024/05/12 23:04:11 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(char c)
{
	if (c == 32 || (c < 14 && c > 8))
		return (1);
	return (0);
}

size_t	len_literal_word(char *s, int pos)
{
	size_t len;

	len = 1;
	while (s[pos + len] != '\'' && s[pos + len] != '"' && s[pos + len] != '$' && is_space(s[pos + len]) == 0 && s[pos + len] != '\0')

		len++;
	return (len);
}

size_t len_quotes(char *s, int pos)
{
	size_t	len;

	len = 0;
	while (s[pos + 1 + len] != '\0' && s[pos + 1 + len] != s[pos])
		len++;
	return (len);
}

int	something_to_add(char *s, int pos)
{
	if (s[pos] == '\'' || s[pos] == '"' || s[pos] == '$' || ft_isalnum(s[pos]) == 1)
		return (1);
	return (0);
}

char *obtain_variable(char *s, int i)
{
	char *var_name;
	char *var_value;
	size_t len;

	len = len_literal_word(s, i);
	var_name = ft_substr(s, i, len);
	var_value = getenv(var_name);
	free(var_name);
	if (var_value == 0)
		return (NULL);
	return (var_value);
}

char	*expand_double_quotes(char *s, int pos)
{
	int		len;
	char	*result;
	char	*aux;
	char	*chunk;

	len = 0;
	while(s[pos + len + 1] != '"')
	{
		while(s[pos + len + 1] != '"' && s[pos + len + 1] != '$')
		{
			len++;
		}
		result = ft_substr(s, pos + 1, len);
		pos = pos + len + 1;
		if (s[pos] == '"')
			return (result);
		if (s[pos] == '$')
		{
			chunk = obtain_variable(s, pos + 1);
			pos += len_literal_word(s, pos + 1);
			aux = result;
			result = ft_strjoin(aux, chunk);
			free(aux);
		}
		len = 0;
	}
	return (result);
}

char *extract_element(char *s, int pos)
{
	size_t	len;
	char	*result;
	char	*chunk;
	char	*aux;

	if (!s)
		return (NULL);
	result = NULL;
	while (s[pos] == '<' || s[pos] == '>' || is_space(s[pos]) == 1)
		pos++;
	while (something_to_add(s, pos) == 1)
	{
		if (s[pos] == '\'')
		{
			len = len_quotes(s, pos);
			chunk = ft_substr(s, pos + 1, len);
			pos = pos + len + 2;aux = result;
			result = ft_strjoin(aux, chunk);
			free(aux);
			free(chunk);
		}
		else if (s[pos] == '"')
		{
			chunk = expand_double_quotes(s, pos);
			pos += len_quotes(s, pos) + 2;
			aux = result;
			result = ft_strjoin(aux, chunk);
			free(aux);
			free(chunk);
		}
		else if (s[pos] == '$')
		{
			chunk = obtain_variable(s, pos + 1);
			pos += len_literal_word(s, pos + 1) + 1;//comprobar si se necesita en más sitios
			aux = result;
			result = ft_strjoin(aux, chunk);
			free(aux);
		}
		else
		{
			len = len_literal_word(s, pos);
			chunk = ft_substr(s, pos, len);
			pos = pos + len;
			aux = result;
			result = ft_strjoin(aux, chunk);
			free(aux);
			free(chunk);
		}
	}
	return (result);
}

int	locate_position(char *s, char c)
{
	int i;

	i = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int extract_input(char *s)
{
	int		fd;
	int		pos;
	char	*filename;

	if (!s)
		return (-1);
	printf("Extract input: string %s\n", s);
	pos = locate_position(s, '<');
	if (pos == -1)
		return (0);
	if (pos == -2)
		return (1);//heredoc
	filename = extract_element(s, pos);
	printf("Filename %s\n", filename);
	fd = open(filename, O_RDONLY);
	free(filename);
	return (fd);
}


/*
Extract file - obtiene el nombre de archivo
Para cuando llega a un espacio que esté fuera de comillas o cuando llega a un símbolo separador



Extract command - obtiene un comando con sus argumentos y lo guarda en un char**

*/
/*
int	obtain_variables_to_expand(char *s, int i, char del)
{
	int		var;
	
	var = 0;
	while (is_delimiter(del, s[i]) == 0 || s[i] == '$')
	{
		if (s[i] == '$')
			var++;
		i++;
	}
	return (var);
}

char *obtain_variable(char *s, int i)
{
	char *var_name;
	char *var_value;

	var_name = obtain_word(s, i + 1, ' ');
	var_value = getenv(var_name);
	if (var_value == 0)
		return (NULL);
	return (var_value);
}

char *expand_string(char *s, int i, char del)
{
	char *result;
	int var;
	int v;
	char *variable;
	char *aux;
	
	var = obtain_variables_to_expand(s, i, del);
	v = 0;
	if (s[i] != '$')
	{
		result = obtain_word(s, i, del);
		i += ft_strlen(result);
	}
	else
		result = NULL;
	while (v < var)
	{
		if (s[i] == '$')
		{
			aux = result;
			v++;
			variable = obtain_variable(s, i);
			i = i + ft_strlen(variable) + 1;
			result = ft_strjoin(aux, variable);
			free(aux);
		}
		else
		{
			aux = result;
			variable = obtain_word(s, i, del);
			i = i + ft_strlen(variable);
			result = ft_strjoin(aux, variable);
			free(aux);
			free(variable);
		}
	}
	return (result);
}
*/
