/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:36:54 by irgonzal          #+#    #+#             */
/*   Updated: 2024/05/19 19:05:42 by irgonzal         ###   ########.fr       */
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

static int	select_variable(char **environ)
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
		if (ft_strncmp(var[0], "PATH", 4) == 0)
		{
			ft_out(var);
			return (i);
		}
		ft_out(var);
		i++;
	}
	return (-1);
}

static char	*get_path(char *s, int i, char **path)
{
	char	*route;
	char	*folder;

	if (s && is_local(s) == 0)
		return (s);
	route = NULL;
	if (s && path && path[i])
	{
		folder = ft_strjoin(path[i], "/");
		if (folder)
		{
			route = ft_strjoin(folder, s);
			free(folder);
		}
	}
	return (route);
}

static char	**get_path_variable(char **environ)
{
	char	*default_path;
	int		path_var;

	path_var = select_variable(environ);
	default_path = "PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin";
	if (path_var == -2)
		return (ft_super_split(default_path, "=:"));
	if (path_var == -1)
		return (NULL);
	return (ft_super_split(environ[path_var], "=:"));
}

static char	*get_route(char *s, char **path)
{
	int		i;
	char	*route;

	i = 1;
	route = get_path(s, i, path);
	while (route != NULL)
	{
		if (access(route, F_OK) == 0 && access(route, X_OK) == 0)
			return (route);
		free(route);
		i++;
		route = get_path(s, i, path);
	}
	return (NULL);
}

char	*command_exists(char *s)
{
	char	*route;
	char	**path;

	route = NULL;
	if (s)
	{
		path = get_path_variable(environ);
		if (!path || is_local(s) == 0)
		{
			if (path)
				ft_out(path);
			return (s);
		}
		route = get_route(s, path);
		ft_out(path);
	}
	return (route);
}