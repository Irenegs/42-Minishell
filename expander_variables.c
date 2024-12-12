/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 00:51:52 by irene             #+#    #+#             */
/*   Updated: 2024/12/13 00:52:46 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*empty_string(void)
{
	char	*var_value;

	var_value = malloc(1 * sizeof(char));
	if (!var_value)
		return (write_error_null(1));
	var_value[0] = '\0';
	return (var_value);
}

char	*ft_getenv(char *var_name, t_mix *data)
{
	int		var_number;
	int		len_var;
	char	*var_value;

	if (ft_strncmp(var_name, "?", 1) == 0)
		var_value = ft_itoa(data->exit_status);
	else
	{
		var_number = select_variable(var_name, data);
		if (var_number == -1)
			return (NULL);
		if (var_number == -2)
			return (empty_string());
		len_var = ft_strlen(var_name);
		var_value = ft_substr(data->m_env[var_number], len_var + 1,
				ft_strlen(data->m_env[var_number]) - len_var - 1);
	}
	if (!var_value)
		return (write_error_null(1));
	return (var_value);
}

static char	*dollar_string(void)
{
	char	*var_value;

	var_value = malloc(2 * sizeof(char));
	if (!var_value)
		return (write_error_null(1));
	var_value[0] = '$';
	var_value[1] = '\0';
	return (var_value);
}

char	*obtain_variable(char *s, int i, t_mix *data)
{
	char	*var_name;
	char	*var_value;
	size_t	len;

	len = len_varname(s, &i);
	if (len == 0)
	{
		if (s[i] == '{')
			return (write_error_null(2));
		if (is_quote(s[i]) != 0 && is_space(s[i + 1]) == 0)
			return (empty_string());
		return (dollar_string());
	}
	if (len > 0 && s[i] == '{')
		var_name = ft_substr(s, i + 1, len - 2);
	else
		var_name = ft_substr(s, i, len);
	if (!var_name)
		return (write_error_null(1));
	var_value = ft_getenv(var_name, data);
	free(var_name);
	return (var_value);
}

char	*expand_variable(char *orig, char *input_str, int pos, t_mix *data)
{
	char	*result;
	char	*chunk;

	chunk = obtain_variable(input_str, pos + 1, data);
	if (!chunk)
		return (NULL);
	result = ft_strjoin(orig, chunk);
	free(orig);
	free(chunk);
	if (!result)
		return (write_error_null(1));
	return (result);
}
