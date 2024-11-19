/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:10:48 by irene             #+#    #+#             */
/*   Updated: 2024/11/18 23:41:08 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_too_many_arguments(t_mix *data)
{
	write(2, "exit: too many arguments\n", 25);
	if (data->exit_status == 0)
		return (1);
	return (data->exit_status);
}

int	ft_exit(char **command, t_mix *data)
{
	int	status;

	status = data->exit_status;
	if (command[1])
	{
		if (command[2])
			return (exit_too_many_arguments(data));
		if (ft_isnum(command[1]) == 1)
		{
			write(2, "exit: numeric argument required\n", 32);
			status = 2;
		}
		else
		{
			status = ft_atoi(command[1]);
			if (status < 0 || status > 255)
				status = (unsigned char)status;
		}
	}
	close_pipes(data->pipes, data->pipesfd);
	clean_and_free_heredocs(data->heredocs, data->pipes);
	free(data->input);
	ft_out(data->m_env);
	exit(status);
}
