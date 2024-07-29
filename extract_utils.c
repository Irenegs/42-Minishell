/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:40:20 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/29 19:34:51 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	if (c == 32 || (c < 14 && c > 8) || c == '\0')
		return (1);
	return (0);
}

size_t	len_literal_word(char *s, int pos)
{
	size_t	len;

	len = 1;
	while (s[pos + len] != '\'' && s[pos + len] != '"' && s[pos + len] != '$'
		&& is_space(s[pos + len]) == 0 && s[pos + len] != '\0')
		len++;
	return (len);
}

size_t	len_delimiter(char *s, int pos)
{
	size_t	len;

	len = 1;
	if (s[pos] == '\'' || s[pos] == '"')
	{
		len = 1;
		while (s[pos + len] != '\0' && s[pos + len] != s[pos])
			len++;
	}
	else
	{
		while (s[pos + len] != '\0' && s[pos + len] != '<'
			&& s[pos + len] != '>' && s[pos + len] != '\''
			&& s[pos + len] != '"' && is_space(s[pos + len]) == 0 && len < 10)
			len++;
	}
	return (len);
}

size_t	len_quotes(char *s, int pos)
{
	size_t	len;

	len = 0;
	while (s[pos + 1 + len] != '\0' && s[pos + 1 + len] != s[pos])
		len++;
	return (len);
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
	int quotes;
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

int	len_cmd_str(char *str)
{
	int	len;
	int	i;
	int	quotes;

	if (!str)
		return (0);
	len = 1;
	i = 0;
	quotes = 0;
	while(str[i] != '\0' && str[i] != '|')
	{
		i++;
		while (str[i] != '\0' && str[i] != '|' && quotes == 0 && (str[i] == '<' || str[i] == '>'))
			i += len_skip_word(str, i);
		manage_quotes(&quotes, str[i]);
		//printf("len++ cuando i=%d->%c:%d\n", i, str[i], str[i]);
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
	while(orig[i] != '\0' && orig[i] != '|')
	{

		while (orig[i] != '\0' && orig[i] != '|' && quotes == 0 && (orig[i] == '<' || orig[i] == '>'))
			i += len_skip_word(orig, i);
		manage_quotes(&quotes, orig[i]);
		res[len] = orig[i];
		len++;
		if (orig[i] != '\0')
			i++;
	}
	res[len] = '\0';
}

char	*extract_cmd_str(char *str)
{
	int	len;
	char	*cmd;

	if (!str || len_cmd_str(str) == 0)
		return (NULL);
	len = len_cmd_str(str);
	cmd = malloc((len + 1) * sizeof(char));
	if (!cmd)
		return (NULL);//write_error_null(1)
	copy_cmd(str, cmd);
	return (cmd);
}
