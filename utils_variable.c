/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:32:38 by irene             #+#    #+#             */
/*   Updated: 2024/12/13 00:52:33 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	select_variable(char *var_name, t_mix *data)
{
	int		i;
	char	**var;

	if (!data->m_env || data->m_env[0] == NULL)
		return (-2);
	i = 0;
	while (data->m_env[i])
	{
		var = ft_super_split(data->m_env[i], "=:");
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
	return (-2);
}

size_t	len_varvalue(char *str, int pos)
{
	size_t	len;

	if (!str)
		return (0);
	if (str[pos] == '?')
		return (1);
	if (str[pos] == '{')
		(pos)++;
	if (str[pos] != '_' && ft_isalpha(str[pos]) == 0)
		return (0);
	len = 1;
	while (str[pos + len] == '_' || ft_isalnum(str[pos + len]))
		len++;
	if (str[pos - 1] == '{')
		len = len + 2;
	return (len);
}

size_t	len_varname(char *str, int *pos)
{
	size_t	len;

	if (!str)
		return (0);
	if (str[*pos] == '?')
		return (1);
	if (str[*pos] == '{' && str[*pos + 2] != '_'
		&& ft_isalpha(str[*pos + 2]) == 0)
		return (0);
	if (str[*pos] == '{')
		(*pos)++;
	if (str[*pos] != '_' && ft_isalpha(str[*pos]) == 0)
		return (0);
	len = 1;
	while (str[*pos + len] == '_' || ft_isalnum(str[*pos + len]))
		len++;
	return (len);
}
