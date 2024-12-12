/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:36:03 by irgonzal          #+#    #+#             */
/*   Updated: 2024/12/12 22:33:28 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_cmd(char *orig, char *res)
{
	int	len;
	int	i;
	int	quotes;

	if (!orig || !res)
		return ;
	len = 0;
	i = 0;
	quotes = 0;
	while (orig[i] != '\0' && (orig[i] != '|' || quotes != 0))
	{
		while (orig[i] != '\0' && orig[i] != '|' && quotes == 0
			&& (orig[i] == '<' || orig[i] == '>'))
			i += len_skip_word(orig, i);
		manage_quotes(&quotes, orig[i]);
		res[len] = orig[i];
		len++;
		if (orig[i] != '\0')
			i++;
	}
	res[len] = '\0';
}

static char	*extract_cmd_str(char *str)
{
	int		len;
	char	*cmd;

	if (!str || len_cmd_str(str) == 0)
		return (NULL);
	len = len_cmd_str(str);
	cmd = malloc((len + 1) * sizeof(char));
	if (!cmd)
		return (write_error_null(1));
	copy_cmd(str, cmd);
	return (cmd);
}

char	**extract_command(char *s, t_mix *data)
{
	int		pos;
	char	*cmd_string;
	char	**command;

	pos = locate_cmd_position(s);
	if (pos == -1)
	{
		*s = '\0';
		return (NULL);
	}
	cmd_string = extract_cmd_str(s);
	if (!cmd_string)
		return (NULL);
	command = split_command(cmd_string, data);
	free(cmd_string);
	return (command);
}
