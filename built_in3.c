/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 22:04:50 by pablo             #+#    #+#             */
/*   Updated: 2024/07/27 19:10:52 by irgonzal         ###   ########.fr       */
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

int	ft_env(t_mix *data)
{
	int	j;

	j = 0;
	while (data->m_env[j])
	{
		if (ft_strchr(data->m_env[j], '='))
			printf("%s\n", data->m_env[j]);
		j++;
	}
	return (0);
}

int	ft_exit(char **command, t_mix *data)
{
	int	status;

	status = data->exit_status;
	if (command[1])
	{
		if (ft_isnum(command[1]) == 1)
		{
			printf("exit: %s: numeric argument required\n", command[1]);
			status = 2;
		}
		else
			status = ft_atoi(command[1]);
	}
	close_pipes(data->pipes, data->pipesfd);
	clean_and_free_heredocs(data->heredocs, data->pipes);
	free(data->input);
	ft_out(data->m_env);
	exit(status);
}

int	execute_builtin(t_mix *data, char **command)
{
	if (ft_strcmp(command[0], "echo") == 0)
		return (ft_echo(command));
	else if (ft_strcmp(command[0], "cd") == 0)
		return (ft_cd(command, data));
	else if (ft_strcmp(command[0], "pwd") == 0)
		return (ft_pwd(data));
	else if (ft_strcmp(command[0], "exit") == 0)
		return (ft_exit(command, data));
	else if (ft_strcmp(command[0], "export") == 0)
		return (ft_export(data, command));
	else if (ft_strcmp(command[0], "unset") == 0)
		return (ft_unset(data, command));
	else if (ft_strcmp(command[0], "env") == 0)
		return (ft_env(data));
	else
	{
		fprintf(stderr, "%s: command not found\n", command[0]);//fprintf NO
		return (1);
	}
}

int	ft_isnum(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
