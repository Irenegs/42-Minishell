/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:42:48 by irgonzal          #+#    #+#             */
/*   Updated: 2024/12/01 19:24:30 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	something_to_add(char *s, int pos)
{
	if (is_space(s[pos]) == 0 && s[pos] != '<' && s[pos] != '>'
		&& s[pos] != '|')
		return (1);
	return (0);
}

void	free_array(char ***arr)
{
	int	i;
	int	j;

	i = 0;
	while (arr && arr[i])
	{
		j = 0;
		while (arr[i] && arr[i][j])
		{
			free(arr[i][j]);
			j++;
		}
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	execute_pipes(t_mix *data)
{
	int	ret_value;

	ret_value = 0;
	if (data->pipes != 0)
	{
		data->pipesfd = malloc((data->pipes) * 2 * sizeof(int));
		if (!data->pipesfd)
			return (write_error_int(1, 1));
		ret_value = execute_several_pipes(data);
		free(data->pipesfd);
	}
	else
		ret_value = execute_zero_pipes(data);
	return (ret_value);
}
