/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:21:12 by irene             #+#    #+#             */
/*   Updated: 2024/09/22 17:54:35 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_content(char *orig, char *res, int *pos, int len)
{
	int	i;

	if (!orig || !res || len == 0)
		return ;
	i = 0;
	while (i != len)
	{
		res[i] = orig[*pos];
		i++;
		(*pos)++;
	}
	res[i] = '\0';
}

static int	len_word(char *str, int *pos)
{
	int	len;
	int	quotes;

	if (!str)
		return (0);
	len = 0;
	quotes = 0;
	while ((quotes != 0 || str[*pos + len] != ' ') && str[*pos + len] != '\0')
	{
		if (quotes != 0 && str[*pos + len] == quotes
			&& is_escaped(str,*pos + len) == 0)
			quotes = 0;
		else if (quotes == 0 && is_quote(str[*pos + len]) != 0
			&& is_escaped(str,*pos + len) == 0)
			quotes = str[*pos + len];
		len++;
	}
	return (len);
}

static char	*split_word(char *str, int *pos)
{
	char	*word;
	int		len;

	while (str[*pos] == ' ')
		(*pos)++;
	len = len_word(str, pos);
	printf("split_word:len:%d\n", len);
	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (write_error_null(1));
	copy_content(str, word, pos, len);
	printf("word:%s\n", word);
	while (str[*pos] == ' ')
		(*pos)++;
	return (word);
}

static int	count_words(char *str)
{
	int	words;
	int	i;
	int	quotes;

	if (!str)
		return (0);
	words = 1;
	i = 0;
	quotes = 0;
	while (str && str[i] != '\0')
	{
		if (quotes == 0 && str[i] == ' ')
			words++;
		if (quotes != 0 && str[i] == quotes && str[i - 1] != '\\')
			quotes = 0;
		else if (quotes == 0 && is_quote(str[i]) != 0 && str[i - 1] != '\\')
			quotes = str[i];
		i++;
	}
	return (words);
}

char	**split_element(char *str)
{
	char	**result;
	int		words;
	int		w;
	int		pos;

	words = count_words(str);
	result = malloc((words + 1) * sizeof(char *));
	if (!result)
		return (write_error_null(1));
	pos = 0;
	w = 0;
	while (w < words)
	{
		result[w] = split_word(str, &pos);
		if (!result)
			return (ft_out(result));
		w++;
	}
	result[w] = NULL;
	return (result);
}
