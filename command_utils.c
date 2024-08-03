/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:32:15 by irene             #+#    #+#             */
/*   Updated: 2024/08/03 17:05:20 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_local(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			if (s[i] == '/')
				return (0);
			i++;
		}
	}
	return (1);
}

char	**get_path_variable(t_mix *data)
{
	int		path_var;
	char	**path_value;

	path_var = select_variable("PATH", data);
	if (path_var < 0)
		return (NULL);
	path_value = ft_super_split(data->m_env[path_var], "=:");
	if (!path_value)
		return (write_error_null(1));
	return (path_value);
}
