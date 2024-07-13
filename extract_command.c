/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:36:03 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/13 19:55:31 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_word(char *s, int pos)
{
	int	len;

	len = 0;
	while (s[pos + len] == '<' || s[pos + len] == '>'
		|| is_space(s[pos + len]) == 1)
		len++;
	while (something_to_add(s, pos + len) == 1)
		len += len_literal_word(s, pos + len);
	return (len);
}

static int	locate_cmd_position(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] == '<' || s[i] == '>')
			i += skip_word(s, i);
		if (is_space(s[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	count_arguments(char *cmd_str)
{
	int	i;
	int	args;

	if (!cmd_str)
		return (0);
	args = 1;
	i = 0;
	while (cmd_str[i] != '\0')
	{
		if (cmd_str[i] == '\'' || cmd_str[i] == '"')
			i += len_quotes(cmd_str, i) + 2;
		else
			i += len_literal_word(cmd_str, i);
		while (is_space(cmd_str[i]) == 1 && cmd_str[i] != '\0')
		{
			args++;
			i++;
		}
	}
	return (args);
}

static char	**split_command(char *s, t_mix *data)
{
	char	**arr;
	int		i;
	int		pos;

	arr = malloc((count_arguments(s) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = -1;
	pos = 0;
	while (++i < count_arguments(s))
	{
		while (new_word(s, " ", pos, 0) == 0)
			pos++;
		arr[i] = extract_element(s, &pos, data);
		if (!arr[i])
			return (ft_out(arr));
		while (s[pos] != '\0' && is_space(s[pos]) == 0)
			pos++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**extract_command(char *s, t_mix *data)
{
	int		pos;
	int		len;
	char	*cmd_string;
	char	**command;

	pos = locate_cmd_position(s);
	if (pos == -1)
		return (NULL);
	len = len_cmd(s, pos);
	cmd_string = ft_substr(s, pos, len);
	if (!cmd_string)
		return (NULL);
	command = split_command(cmd_string, data);
	free(cmd_string);
	return (command);
}

/*
extract command: 
devolver {NULL, NULL, NULL} para diferenciar de fallo en el malloc ?
*/