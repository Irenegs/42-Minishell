/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:56:45 by pablo             #+#    #+#             */
/*   Updated: 2024/06/06 22:55:32 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_mix *data)
{
	int	new_line;
	int	i;

	new_line = 1;
	i = 1;

	if (data->m_argv[i] && ft_strcmp(data->m_argv[i], "-n") == 0)
	{
		new_line = 0;
		i++;
	}
	while (data->m_argv[i])
	{
		printf("%s", data->m_argv[i]);
		if (data->m_argv[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
}

void	ft_cd(t_mix *data)
{
	if (!data->m_argv[1])
	{
		printf("cd: missing argument\n");
		return ;
	}
	if (chdir(data->m_argv[1]) != 0)
	{
		perror("cd");
	}
}

void	ft_pwd(void)
{
	char	*pwd;

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

void	ft_export(t_mix *data)
{
	char	**str;
	int		i;

	i = 1;
	if (!data->m_argv[1])
	{
		printf("export: missing argument\n");
		return ;
	}
	while (data->m_argv[i])
	{
		str = ft_split(data->m_argv[i], '=');
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
			printf("export: invalid argument '%s'\n", data->m_argv[i]);
		free_argv(str);
		i++;
	}
}

void	ft_unset(t_mix *data)
{
	int	i;

	i = 1;
	if (!data->m_argv[1])
	{
		printf("unset: missing argument\n");
		return ;
	}

	while (data->m_argv[i])
	{
		data->m_env = remove_env(data->m_env, data->m_argv[i]);
		if (!data->m_env)
		{
			perror("unset");
			return ;
		}
		i++;
	}
}