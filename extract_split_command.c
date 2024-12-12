/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_split_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:25:36 by irene             #+#    #+#             */
/*   Updated: 2024/12/12 22:26:19 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_arguments(char *cmd_str)
{
	int	i;
	int	args;
	int	quotes;

	if (!cmd_str)
		return (0);
	i = 0;
	args = 0;
	quotes = 0;
	while (cmd_str[i] != '\0')
	{
		while (cmd_str[i] == ' ')
			i++;
		if (cmd_str[i] != ' ' && cmd_str[i] != '\0')
		{
			args++;
			manage_quotes(&quotes, cmd_str[i]);
			while (cmd_str[i] != '\0' && (cmd_str[i] != ' ' || quotes != 0))
				manage_quotes(&quotes, cmd_str[++i]);
			if (cmd_str[i] != '\0')
				i++;
		}
	}
	return (args);
}

static char	***initialize_split_command(char *s, int *i, int *pos, t_mix *data)
{
	char	***arr;

	*i = -1;
	*pos = 0;
	if (!s)
		return (NULL);
	arr = malloc((count_arguments(s) + 1) * sizeof(char **));
	if (!arr || !data)
		return (write_error_null(1));
	return (arr);
}

char	**split_command(char *s, t_mix *data)
{
	char	***arr;
	int		i;
	int		pos;
	char	**element;

	arr = initialize_split_command(s, &i, &pos, data);
	if (!arr)
		return (NULL);
	while (arr && ++i < count_arguments(s))
	{
		while (new_word(s, " ", pos, 0) == 0)
			pos++;
		arr[i] = extract_element(s, pos, data);
		if (!arr[i])
		{
			free_array(arr);
			return (NULL);
		}
		while (s[pos] != '\0' && is_space(s[pos]) == 0)
			pos++;
	}
	arr[i] = NULL;
	element = join_arrays(arr);
	free_array(arr);
	return (element);
}
