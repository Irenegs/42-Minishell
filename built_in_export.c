/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:56:45 by pablo             #+#    #+#             */
/*   Updated: 2024/12/11 18:41:28 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	empty_export(t_mix *data)
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
		write(1, data->m_env[n_var] + pos_eq,
			ft_strlen(data->m_env[n_var] + pos_eq));
		write(1, "\"", 1);
		write(1, "\n", 1);
		n_var++;
	}
}

static int	process_export_command(t_mix *data, char *cmd)
{
	char	*var_name;
	int		len;

	if (cmd[0] == '=')
		return (write_error_int(5, 1));
	len = locate_char_position(cmd, '=');
	var_name = ft_substr(cmd, 0, len);
	if (!var_name)
		return (write_error_int(1, 1));
	if (valid_varname(var_name) == 1 && len != -1)
	{
		data->m_env = au_env(data->m_env, var_name, cmd + len + 1);
		if (!data->m_env)
		{
			free(var_name);
			return (1);
		}
	}
	else if (valid_varname(var_name) != 1)
	{
		free(var_name);
		return (write_error_int(5, 1));
	}
	free(var_name);
	return (0);
}

int	ft_export(t_mix *data, char **command)
{
	int	i;

	if (!command || !command[1])
	{
		empty_export(data);
		return (0);
	}
	i = 1;
	while (command[i])
	{
		if (process_export_command(data, command[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
