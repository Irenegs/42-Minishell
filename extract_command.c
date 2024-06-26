/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:36:03 by irgonzal          #+#    #+#             */
/*   Updated: 2024/06/06 19:10:17 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_cmd(char *s, int pos)
{
	int	len;

	len = 0;
	while (s[pos + len] != '\0' && s[pos + len] != '<'
		&& s[pos + len] != '>' && s[pos + len] != '|')
		len++;
	while (is_space(s[pos + len]) == 1 || s[pos + len] == '|'
		|| s[pos + len] == '<' || s[pos + len] == '>')
		len--;
	return (++len);
}

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

static char	**split_command(char *s)
{
	char	**arr;
	int		i;
	int		pos;
	int		len;

	arr = malloc((ft_wc(s, " ") + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = -1;
	pos = 0;
	while (++i < ft_wc(s, " "))
	{
		while (new_word(s, " ", pos, 0) == 0)
			pos++;
		arr[i] = extract_element(s, pos);
		if (!arr[i])
			return (ft_out(arr));
		pos += len_literal_word(s, pos);
		while (s[pos] != '\0' && is_space(s[pos]) == 0)
			pos++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**extract_command(char *s)
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
	command = split_command(cmd_string);
	free(cmd_string);
	return (command);
}

/*
extract command: 
devolver {NULL, NULL, NULL} para diferenciar de fallo en el malloc ?
*/