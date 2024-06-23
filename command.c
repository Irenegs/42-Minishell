/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:36:54 by irgonzal          #+#    #+#             */
/*   Updated: 2024/06/23 18:12:14 by pablgarc         ###   ########.fr       */
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

static char	*command_exists(char *s)
{
	char	*route;
	char	**path;

	route = NULL;
	if (s)
	{
		path = ft_super_split(getenv("PATH"), "=:");
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

int	run_command(char **command, t_mix *data)
{
	char	*cmd;

	if (!command)
		return (-1);
	if (is_builtin(command[0]))
	{
		execute_builtin(data, command);
		//devuelve codigo de salida
		return (0);
	}
	cmd = command_exists(command[0]);
	if (!cmd)
		return (127);
	execve(cmd, command, data->m_env);
	ft_out(command);
	return (-1);
}
