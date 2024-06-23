/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:31:28 by pablgarc          #+#    #+#             */
/*   Updated: 2024/06/20 19:55:57 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	cd_error(t_mix *data, char **cmd_args)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(cmd_args[1], 2);
	ft_putstr_fd(": Invalid option\n", 2);
	free_child(data, cmd_args, 0);
	exit (2);
}

void	command_error(char *command, char **cmd_args, t_mix *data)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	free_child(data, cmd_args, 0);
	data->exit_status = 127;
	exit(127);
}

void	permission_error(char **cmd_args, t_mix *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_args[0], 2);
	ft_putstr_fd(": Permission denied\n", 2);
	free_child(data, cmd_args, 0);
	data->exit_status = 126;
	exit(126);
}

void	file_error(char **cmd_args, t_mix *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_args[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_child(data, cmd_args, 0);
	data->exit_status = 127;
	exit(127);
}

void	is_a_directory(char **cmd_args, t_mix *data)
{
	ft_putstr_fd(cmd_args[0], 2);
	ft_putstr_fd(": Is a directory\n", 2);
	free_child(data, cmd_args, 0);
	data->exit_status = 126;
	exit(126);
}
