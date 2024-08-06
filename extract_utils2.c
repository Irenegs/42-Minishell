/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:08:50 by pablgarc          #+#    #+#             */
/*   Updated: 2024/08/06 17:08:22 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_cmd_str(char *str)
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

void	manage_quotes(int *quotes, char c)
{
	if (c == *quotes && *quotes != 0)
		*quotes = 0;
	else if (*quotes == 0 && (c == '\'' || c == '"'))
		*quotes = c;
}

int	len_skip_word(char *str, int pos)
{
	int	quotes;
	int	len;

	if (!str)
		return (0);
	quotes = 0;
	len = 1;
	while (str[pos + len] == ' ')
		len++;
	while (str[pos + len] != '\0' && (quotes != 0 || str[pos + len] != ' '))
	{
		manage_quotes(&quotes, str[pos + len]);
		len++;
	}
	return (len);
}

void	copy_cmd(char *orig, char *res)
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

int	locate_char_position(char *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
