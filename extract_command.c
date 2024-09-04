/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:36:03 by irgonzal          #+#    #+#             */
/*   Updated: 2024/09/04 18:06:55 by irgonzal         ###   ########.fr       */
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
	int	quotes;

	//printf("cmd_str:%s->%ld\n", cmd_str, ft_strlen(cmd_str));
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
			//printf("args++ cuando %c\n", cmd_str[i]);
			manage_quotes(&quotes, cmd_str[i]);
			while (cmd_str[i] != '\0' && (cmd_str[i] != ' ' || quotes != 0))
			{
				i++;
				manage_quotes(&quotes, cmd_str[i]);
			}
			if (cmd_str[i] != '\0')
				i++;
		}
	}
	return (args);
}

static char	**split_command(char *s, t_mix *data)
{
	char	***arr;
	int		i;
	int		pos;
	char	**element;

	arr = malloc((count_arguments(s) + 1) * sizeof(char **));
	if (!arr || !data)
		return (write_error_null(1));
	i = -1;
	pos = 0;
	while (++i < count_arguments(s))
	{
		while (new_word(s, " ", pos, 0) == 0)
			pos++;
		arr[i] = extract_element(s, pos, data);
		if (!arr[i])
		{
			//ft_out(arr);
			return (NULL);//write_error_null(1));
		}
		while (s[pos] != '\0' && is_space(s[pos]) == 0)
			pos++;
	}
	arr[i] = NULL;
	element = join_arrays(arr);
	free(arr);//revisar
	return (element);
}

char	**extract_command(char *s, t_mix *data)
{
	int		pos;
	char	*cmd_string;
	char	**command;

	pos = locate_cmd_position(s);
	if (pos == -1)
		return (NULL);
	cmd_string = extract_cmd_str(s);
	//printf("cmd_string %s\n", cmd_string);
	if (!cmd_string)
		return (NULL);
	command = split_command(cmd_string, data);
	/*
	int i = 0;
	while (command[i])
	{
		printf("command[%d]:%s\n", i, command[i]);
		i++;
	}
	free(cmd_string);
	*/
	return (command);
}
