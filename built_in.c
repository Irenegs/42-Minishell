/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:56:45 by pablo             #+#    #+#             */
/*   Updated: 2024/08/06 16:52:40 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **command)
{
	int	new_line;
	int	i;
	printf("echo:%s\n", command[1]);
	new_line = 1;
	i = 1;
	if (command[i] && ft_strcmp(command[i], "-n") == 0)
	{
		new_line = 0;
		i++;
	}
	while (command[i])
	{
		printf("%s", command[i]);
		if (command[i + 1])
			printf(" ");
		i++;
	}
	if (new_line != 0)
		printf("\n");
	return (0);
}

int	ft_cd(char **command, t_mix *data)
{
	char	*home_dir;

	if (!command[1])
	{
		home_dir = ft_getenv("HOME", data);
		if (home_dir == NULL)
			return (write_error_int(4, 1));
		if (chdir(home_dir) != 0)
		{
			free(home_dir);
			return (perror_int(1));
		}
	}
	else if (command[2])
		return (write_error_int(3, 1));
	else if (chdir(command[1]) != 0)
		return (perror_int(1));
	home_dir = getcwd(NULL, 0);
	if (!home_dir)
		return (perror_int(1));
	au_env(data->m_env, "PWD", home_dir);
	free(home_dir);
	return (0);
}

int	ft_pwd(t_mix *data)
{
	char	*pwd;

	pwd = ft_getenv("PWD", data);
	if (!pwd)
		pwd = getcwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
		return (0);
	}
	return (perror_int(1));
}

int	ft_unset(t_mix *data, char **command)
{
	int	i;

	i = 1;
	if (!command[1])
		return (0);
	while (command[i])
	{
		data->m_env = remove_env(data->m_env, command[i]);
		if (!data->m_env)
		{
			perror("unset");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_export(t_mix *data, char **command)
{
	int	i;

	if (!command || !command[1])
	{
		empty_export(data);
		return (0);
	}
	i = 1;
	while (command[i])
	{
		if (process_export_command(data, command[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
