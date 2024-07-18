/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:31:28 by pablgarc          #+#    #+#             */
/*   Updated: 2024/07/16 20:05:42 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		perror_int(int return_value)
{
	perror(NULL);
	return (return_value);
}


int	write_error_int(int error_code, int return_value)
{
	if (error_code == 1)
		write(2, "Malloc error\n", 13);
	if (error_code == 2)
		write(2, "Write heredoc error\n", 20);
	return (return_value);
}

void	*write_error_null(int error_code)
{
	if (error_code == 1)
		write(2, "Malloc error\n", 13);
	return (NULL);
}
/*
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
*/