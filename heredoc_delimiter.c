/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_delimiter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:07:59 by irene             #+#    #+#             */
/*   Updated: 2024/08/26 18:58:51 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	len_delimiter(char *s)
{
	size_t	len;
	int		quotes;
	int		quotes_quantity;

	len = 0;
	quotes_quantity = 0;
	while (s[len] != '\0' && (s[len] != ' ' && s[len] != '<' && s[len] != '>' && s[len] != '|'))
	{
		if (s[len] == '\'' || s[len] == '"')
		{
			quotes_quantity++;
			quotes = s[len];
			len++;
			while (s[len] != '\0' && s[len] != quotes)
				len++;
			len++;
		}
		else
		{
			while (s[len] != '\0' && s[len] != '<'
				&& s[len] != '>' && s[len] != '\''
				&& s[len] != '"' && is_space(s[len]) == 0)
				len++;
		}
	}
	return (len - 2 * quotes_quantity);
}

static void	copy_delimiter(char *orig, char *res, size_t len)
{
	int	i;
	int j;
	int	quotes;

	i = 0;
	j = 0;
	while (orig[i] != '\0' && (orig[i] != ' ' && orig[i] != '<' && orig[i] != '>' && orig[i] != '|'))
	{
		if (orig[i] == '\'' || orig[i] == '"')
		{
			quotes = orig[i];
			i++;
			while (orig[i] != '\0' && orig[i] != quotes)
				res[j++] = orig[i++];
			i++;
		}
		else
		{
			while (orig[i] != '\0' && orig[i] != '<'
				&& orig[i] != '>' && orig[i] != '\''
				&& orig[i] != '"' && is_space(orig[i]) == 0)
				res[j++] = orig[i++];
		}
	}
	res[len] = '\0';
}

char	*obtain_delimiter(char *del_str)
{
	char	*delimiter;
	int		len;

	while (*del_str != '<')
		del_str++;
	while (*del_str == '<' || is_space(*del_str))
		del_str++;
	len = len_delimiter(del_str);
	delimiter = malloc(len + 1);
	if (!delimiter)
		return (write_error_null(1));
	copy_delimiter(del_str, delimiter, len);
	printf("Delimiter:%s\n", delimiter);
	return (delimiter);
}
