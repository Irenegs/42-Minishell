/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:32:15 by irene             #+#    #+#             */
/*   Updated: 2024/07/12 20:34:10 by irene            ###   ########.fr       */
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

	path_var = select_variable("PATH", environ);
	if (path_var < 0)
		return (NULL);
	return (ft_super_split(environ[path_var], "=:"));
}
