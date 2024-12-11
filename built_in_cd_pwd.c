/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:16:33 by irene             #+#    #+#             */
/*   Updated: 2024/12/11 18:34:05 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **command, t_mix *data)
{
	char	*home_dir;

	if (!command[1])
	{
		home_dir = ft_getenv("HOME", data);
		if (home_dir == NULL)
			return (write_error_int(4, 1));
		if (chdir(home_dir) != 0)
		{
			free(home_dir);
			return (perror_int(1));
		}
	}
	else if (command[2])
		return (write_error_int(3, 1));
	else if (chdir(command[1]) != 0)
		return (perror_int(1));
	home_dir = getcwd(NULL, 0);
	if (!home_dir)
		return (perror_int(1));
	au_env(data->m_env, "PWD", home_dir);
	free(home_dir);
	return (0);
}

int	ft_pwd(t_mix *data)
{
	char	*pwd;

	pwd = ft_getenv("PWD", data);
	if (!pwd)
		pwd = getcwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
		return (0);
	}
	return (perror_int(1));
}
