/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 22:04:50 by pablo             #+#    #+#             */
/*   Updated: 2024/07/30 19:57:56 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (command[2])
		{
			write(2, "exit: too many arguments\n", 25);
			return (1);
		}
		if (ft_isnum(command[1]) == 1)
		{
			write(2, "exit: numeric argument required\n", 32);
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
