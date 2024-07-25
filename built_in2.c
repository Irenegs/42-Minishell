/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:56:45 by pablo             #+#    #+#             */
/*   Updated: 2024/07/24 20:24:19 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **command)
{
	int	new_line;
	int	i;

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
	if (new_line)
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
		{
			write(2, "cd: HOME not set\n", 17);
			return (1);
		}
		else
		{
			free(home_dir);
			return (perror_int(1));
		}
		free(home_dir);
	}
	else if (chdir(command[1]) != 0)
		return (perror_int(1));
	home_dir = getcwd(NULL, 0);
	if (!home_dir)
		return (perror_int(1));
	add_or_update_env(data->m_env, "PWD", home_dir);
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

void	empty_export(t_mix *data)
{
	int	n_var;
	int	pos_eq;

	if (!data || !data->m_env)
		return ;
	n_var = 0;
	while (data->m_env[n_var] != NULL)
	{
		pos_eq = locate_char_position(data->m_env[n_var], '=') + 1;
		write(1, "declare -x ", 11);
		write(1, data->m_env[n_var], pos_eq);
		write(1, "\"", 1);
		write(1, data->m_env[n_var] + pos_eq, ft_strlen(data->m_env[n_var] + pos_eq));
		write(1, "\"", 1);
		write(1, "\n", 1);
		n_var++;
	}
}

int	ft_export(t_mix *data, char **command)
{
	char	**str;
	int		i;

	i = 1;
	if (!command[1])
		empty_export(data);
	while (command[i])
	{
		str = ft_split(command[i], '=');
		if (str[0] && str[1])
		{
			data->m_env = add_or_update_env(data->m_env, str[0], str[1]);
			if (!data->m_env)
			{
				perror("export");
				return (1);
			}
		}
		else
			printf("export: invalid argument '%s'\n", command[i]);
		free_argv(str);
		i++;
	}
	return (0);
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
