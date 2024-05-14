/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:23:01 by irgonzal          #+#    #+#             */
/*   Updated: 2024/05/14 21:50:40 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_out(char **arr)
{
	int	j;

	j = 0;
	while (arr[j])
	{
		free(arr[j]);
		j++;
	}
	free(arr);
	return (NULL);
}

static int	ch_to_print(char const *s, int i)
{
	if (s[i] == '\\' || s[i] == '\'')
	{
		if (is_escaped(s, i) == 0)
			return (0);
	}
	return (1);
}

static int	len_next_word(char const *s, char *sep, int pos)
{
	int	len;
	int	i;
	int	quotes;

	i = 0;
	len = 0;
	quotes = 0;
	while (end_word(s, sep, pos + i, quotes) == 0)
	{
		if (ch_to_print(s, pos + i) == 1)
			len++;
		else if (s[pos + i] == '\'')
			quotes = 1 - quotes;
		i++;
	}
	return (len);
}

static int	copy_return_nonprint(char *dst, char const *s, int len)
{
	int	i;
	int	nonprintable;

	i = 0;
	nonprintable = 0;
	if (dst && s)
	{
		while (i < len)
		{
			if (ch_to_print(s, i + nonprintable) == 1)
			{
				dst[i] = s[i + nonprintable];
				i++;
			}
			else
				nonprintable++;
		}
		dst[len] = '\0';
		return (nonprintable);
	}
	return (-1);
}

char	**ft_super_split(char const *s, char *sep)
{
	char	**arr;
	int		i;
	int		pos;
	int		len;

	arr = malloc((ft_wc(s, sep) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = -1;
	pos = 0;
	while (++i < ft_wc(s, sep))
	{
		while (new_word(s, sep, pos, 0) == 0)
			pos++;
		len = len_next_word(s, sep, pos);
		arr[i] = malloc((len + 1) * sizeof(char));
		if (!arr[i])
			return (ft_out(arr));
		pos = pos + len + copy_return_nonprint(arr[i], s + pos, len) + 1;
	}
	arr[i] = NULL;
	return (arr);
}