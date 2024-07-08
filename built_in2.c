/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:56:45 by pablo             #+#    #+#             */
/*   Updated: 2024/07/06 13:25:35 by pablgarc         ###   ########.fr       */
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

int	ft_cd(char **command)
{
	char	*home_dir;

	printf("command:%s\n", command[1]);

	if (!command[1] || command[1][0] == '\0')
	{
		// Si no hay argumento o el argumento está vacío, cambiar al directorio home
		home_dir = getenv("HOME");
		if (home_dir == NULL)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
		if (chdir(home_dir) != 0)
		{
			perror("cd");
		}
		return (1);
	}
	if (chdir(command[1]) != 0)
	{
		perror("cd");
	}
	return (0);
}

int	ft_pwd(void)
{
	char	*pwd;

	printf("builtin\n");
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	else
	{
		perror("pwd");
		return (1);
	}
	return (0);
}


int	ft_export(t_mix *data, char **command)
{
	char	**str;
	int		i;

	i = 1;
	if (!command[1])
	{
		printf("export: missing argument\n");
		return (1);
	}
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
	printf("builtin\n");
	if (!command[1])
	{
		printf("unset: missing argument\n");
		return (1);
	}

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
