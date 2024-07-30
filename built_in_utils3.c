/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:04:24 by pablgarc          #+#    #+#             */
/*   Updated: 2024/07/30 18:24:41 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		write(1, data->m_env[n_var] + pos_eq,
			ft_strlen(data->m_env[n_var] + pos_eq));
		write(1, "\"", 1);
		write(1, "\n", 1);
		n_var++;
	}
}

int	process_export_command(t_mix *data, char *cmd)
{
	char	*var_name;
	int		len;

	len = locate_char_position(cmd, '=');
	var_name = ft_substr(cmd, 0, len);
	if (!var_name)
		return (write_error_int(1, 1));
	if (valid_varname(var_name) == 1)
	{
		if (len != -1)
		{
			data->m_env = au_env(data->m_env, var_name, cmd + len + 1);
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
	return (0);
}
