/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:31:25 by pablo             #+#    #+#             */
/*   Updated: 2024/05/23 23:00:52 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else
		return (0);
}

int is_special_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else
		return (0);
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
	return (1);
}
