/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 22:04:50 by pablo             #+#    #+#             */
/*   Updated: 2024/06/06 23:06:56 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	c;
	unsigned char	d;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		c = (unsigned char)s1[i];
		d = (unsigned char)s2[i];
		if (c != d)
			return (c - d);
		i++;
	}

	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_env(t_mix *data)
{
	int	j;
  
  	if (!data || !data->m_env)
        return;
	j = 0;
	while (data->m_env[j])
	{
		if (ft_strchr(data->m_env[j], '='))
			printf("%s\n", data->m_env[j]);
		j++;
	}
}

void	ft_exit(t_mix *data)
{
	int	status;

	status = 0;
	if (data->m_argv[1])
	{
		status = ft_atoi(data->m_argv[1]);
	}
	exit(status);
}

void	execute_builtin(t_mix *data)
{
	if (ft_strcmp(data->m_argv[0], "echo") == 0)
		ft_echo(data);
	else if (ft_strcmp(data->m_argv[0], "cd") == 0)
		ft_cd(data);
	else if (ft_strcmp(data->m_argv[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(data->m_argv[0], "exit") == 0)
		ft_exit(data);
	else if (ft_strcmp(data->m_argv[0], "export") == 0)
		ft_export(data);
	else if (ft_strcmp(data->m_argv[0], "unset") == 0)
		ft_unset(data);
	else if (ft_strcmp(data->m_argv[0], "env") == 0)
		ft_env(data);
	else if (ft_strcmp(data->m_argv[0], "sleep") == 0)
		ft_sleep(data);
	else
		fprintf(stderr, "%s: command not found\n", data->m_argv[0]);
}
