/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:32:15 by irene             #+#    #+#             */
/*   Updated: 2024/07/12 18:42:28 by irene            ###   ########.fr       */
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

char	**get_path_variable(char **environ)
{
	int		path_var;

	path_var = select_variable("PATH", environ);
	if (path_var < 0)
		return (NULL);
	return (ft_super_split(environ[path_var], "=:"));
}
