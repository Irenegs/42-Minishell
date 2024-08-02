/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:32:38 by irene             #+#    #+#             */
/*   Updated: 2024/07/31 17:50:24 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	select_variable(char *var_name, char **environ)
{
	int		i;
	char	**var;

	if (!environ || environ[0] == NULL)
		return (-2);
	i = 0;
	while (environ[i])
	{
		var = ft_super_split(environ[i], "=:");
		if (!var)
			return (write_error_int(1, -1));
		if (ft_strncmp(var[0], var_name, ft_strlen(var_name) + 1) == 0)
		{
			ft_out(var);
			return (i);
		}
		ft_out(var);
		i++;
	}
	return (-1);
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
		var_number = select_variable(var_name, data->m_env);
		if (var_number < 0)
			return (NULL);
		len_var = ft_strlen(var_name);
		var_value = ft_substr(data->m_env[var_number], len_var + 1,
				ft_strlen(data->m_env[var_number]) - len_var - 1);
	}
	if (!var_value)
		return (write_error_null(1));
	return (var_value);
}

size_t	len_variable(char *str, int pos)
{
	size_t	len;

	if (!str)
		return (0);
	if (str[pos] == '?')
		return (1);
	if (str[pos] != '_' && ft_isalpha(str[pos]) == 0)
		return (0);
	len = 1;
	while (str[pos + len] == '_' || ft_isalnum(str[pos + len]))
		len++;
	return (len);
}

char	*obtain_variable(char *s, int i, t_mix *data)
{
	char	*var_name;
	char	*var_value;
	size_t	len;

	len = len_variable(s, i);
	if (len == 0)
	{
		var_value = malloc(2 * sizeof(char));
		if (!var_value)
			return (write_error_null(1));
		var_value[0] = '$';
		var_value[1] = '\0';
		return (var_value);
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
