/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:56:45 by pablo             #+#    #+#             */
/*   Updated: 2024/06/23 18:05:57 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **command)
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
}

void	ft_cd(char **command)
{
	printf("builtin\n");
	if (!command[1] || command[1][0] == '\0')
	{
		// Si no hay argumento o el argumento está vacío, cambiar al directorio home
		char *home_dir = getenv("HOME");
		if (home_dir == NULL)
		{
			printf("cd: HOME not set\n");
			return;
		}
		if (chdir(home_dir) != 0)
		{
			perror("cd");
		}
		return;
	}
	if (chdir(command[1]) != 0)
	{
		perror("cd");
	}
}

void	ft_pwd(void)
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
	}
}

void	ft_export(t_mix *data, char **command)
{
	char	**str;
	int		i;

	printf("builtin\n");
	i = 1;
	if (!command[1])
	{
		printf("export: missing argument\n");
		return ;
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
				return ;
			}
		}
		else
			printf("export: invalid argument '%s'\n", command[i]);
		free_argv(str);
		i++;
	}
}

void	ft_unset(t_mix *data, char **command)
{
	int	i;

	i = 1;
	if (!command[1])
	{
		printf("unset: missing argument\n");
		return ;
	}

	while (command[i])
	{
		data->m_env = remove_env(data->m_env, command[i]);
		if (!data->m_env)
		{
			perror("unset");
			return ;
		}
		i++;
	}
}