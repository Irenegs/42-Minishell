/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:32:15 by irene             #+#    #+#             */
/*   Updated: 2024/07/16 20:30:38 by irene            ###   ########.fr       */
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

char	**get_path_variable(char **environ)
{
	int		path_var;
	char	**path_value;

	path_var = select_variable("PATH", environ);
	if (path_var < 0)
		return (NULL);
	path_value = ft_super_split(environ[path_var], "=:");
	if (!path_value)
		return (write_error_null(1));
	return (path_value);
}
