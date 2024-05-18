/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:36:03 by irgonzal          #+#    #+#             */
/*   Updated: 2024/05/18 18:38:27 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int len_cmd(char *s, int pos)
{
	int len;

	len = 0;
	while (s[pos + len] != '\0' && s[pos + len] != '<' && s[pos + len] != '>' && s[pos + len] != '|')
		len++;
	while(is_space(s[pos + len]) == 1 || s[pos + len] == '|' || s[pos + len] == '<' || s[pos + len] == '>')
        len--;
	return (++len);
}

static int skip_word(char *s, int pos)
{
	int len;

	len = 0;
	while (s[pos + len] == '<' || s[pos + len] == '>' || is_space(s[pos + len]) == 1)
		len++;
	while (something_to_add(s, pos + len) == 1)
	{
		len += len_literal_word(s, pos + len);
	}
	return (len);
}

static int locate_cmd_position(char *s)
{
	int i;

	i = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] == '<' || s[i] == '>')
			i += skip_word(s, i);
		if (ft_isalnum(s[i]) == 1)
		{
			return (i);
		}
		i++;
	}
	printf("i, si: %d %c\n", i, s[i]);
	return (-1);
}

char **extract_command(char *s)
{
	int		pos;
	int		len;
	char	*cmd_string;
	char	**command;

	pos = locate_cmd_position(s);
	if (pos == -1)
		return (NULL);//devolver {NULL, NULL, NULL} para diferenciar de fallo en el malloc(?)
	len = len_cmd(s, pos);
	cmd_string = ft_substr(s, pos, len);
	printf("cmd substr:%s\n", cmd_string);
	command = ft_super_split(cmd_string, " ");
	free(cmd_string);
	return (command);
}
