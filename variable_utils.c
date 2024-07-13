/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:32:38 by irene             #+#    #+#             */
/*   Updated: 2024/07/12 21:33:28 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	select_variable(char *var_name, char **environ)
{
	int		i;
	char	**var;

	i = 0;
	if (environ[0] == NULL)
		return (-2);
	while (environ[i])
	{
		var = ft_super_split(environ[i], "=:");
		if (!var)
			return (-1);
		if (ft_strncmp(var[0], var_name, ft_strlen(var_name)) == 0)
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
	int	var_number;
	int	len_var;

	if (ft_strncmp(var_name, "?", 1) == 0)
		return (ft_itoa(data->exit_status));
	var_number = select_variable(var_name, data->m_env);
	if (var_number < 0)
		return (NULL);
	len_var = ft_strlen(var_name);
	return (ft_substr(data->m_env[var_number], len_var + 1,
			ft_strlen(data->m_env[var_number]) - len_var - 1));
}

char	*obtain_variable(char *s, int i, t_mix *data)
{
	char	*var_name;
	char	*var_value;
	size_t	len;

	len = len_literal_word(s, i);
	if (len > 0 && s[i] == '{')
		var_name = ft_substr(s, i + 1, len - 2);
	else
		var_name = ft_substr(s, i, len);
	if (!var_name)
		return (NULL);
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
	return (result);
}
