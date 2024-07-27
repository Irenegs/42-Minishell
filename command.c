/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:36:54 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/27 20:10:21 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!folder)
			return (write_error_null(1));
		route = ft_strjoin(folder, s);
		free(folder);
		if (!route)
			return (write_error_null(1));
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

static char	*command_exists(char *s, char **env)
{
	char	*route;
	char	**path;

	route = NULL;
	if (s)
	{
		if (is_local(s) == 0)
			return (s);
		path = get_path_variable(env);
		if (!path)
			return (s);
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
	if (is_builtin(command[0]) == 1)
		return (execute_builtin(data, command));
	cmd = command_exists(command[0], data->m_env);
	if (!cmd)
		cmd = command[0];
	execve(cmd, command, data->m_env);
	perror(NULL);
	if (ft_strncmp(cmd, command[0], ft_strlen(command[0])) != 0)
		free(cmd);
	return (127);
}
