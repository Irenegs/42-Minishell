/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:56:45 by pablo             #+#    #+#             */
/*   Updated: 2024/07/27 20:11:42 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **command)
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
	return (0);
}

int	ft_cd(char **command, t_mix *data)
{
	char	*home_dir;

	if (!command[1])
	{
		home_dir = ft_getenv("HOME", data);
		if (home_dir == NULL)
		{
			write(2, "cd: HOME not set\n", 17);
			return (1);
		}
		if (chdir(home_dir) != 0)
		{
			free(home_dir);
			return (perror_int(1));
		}
	}
	else if (chdir(command[1]) != 0)
		return (perror_int(1));
	home_dir = getcwd(NULL, 0);
	if (!home_dir)
		return (perror_int(1));
	add_or_update_env(data->m_env, "PWD", home_dir);
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

void	empty_export(t_mix *data)
{
	int	n_var;
	int	pos_eq;

	if (!data || !data->m_env)
		return ;
	n_var = 0;
	while (data->m_env[n_var] != NULL)
	{
		pos_eq = locate_char_position(data->m_env[n_var], '=') + 1;
		write(1, "declare -x ", 11);
		write(1, data->m_env[n_var], pos_eq);
		write(1, "\"", 1);
		write(1, data->m_env[n_var] + pos_eq, ft_strlen(data->m_env[n_var] + pos_eq));
		write(1, "\"", 1);
		write(1, "\n", 1);
		n_var++;
	}
}

int	valid_varname(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] != '\0')
	{
		if (i == 0 && ft_isdigit(str[i]) != 0)
			return (0);
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(t_mix *data, char **command)
{
	char	*var_name;
	int		i;
	int		len;

	if (!command || !command[1])
		empty_export(data);
	i = 1;
	while (command[i])
	{
		len = locate_char_position(command[i], '=');
		var_name = ft_substr(command[i], 0, len);
		if (!var_name)
			return (write_error_int(1, 1));
		if (valid_varname(var_name) == 1)
		{
			if (len != -1)
			{
				data->m_env = add_or_update_env(data->m_env, var_name, command[i] + len + 1);
				if (!data->m_env)
				{
					free(var_name);
					return (1);
				}
			}	
		}
		else
			write(2, "Not a valid identifier\n", 23);
		free(var_name);
		i++;
	}
	return (0);
}

int	ft_unset(t_mix *data, char **command)
{
	int	i;

	i = 1;
	if (!command[1])
		return (0);
	while (command[i])
	{
		data->m_env = remove_env(data->m_env, command[i]);
		if (!data->m_env)
		{
			perror("unset");
			return (1);
		}
		i++;
	}
	return (0);
}
