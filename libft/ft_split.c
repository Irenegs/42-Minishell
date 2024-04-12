/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:53:17 by irgonzal          #+#    #+#             */
/*   Updated: 2022/09/30 08:36:59 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wc(char const *s, char c)
{
	int	i;
	int	words;

	if (!s)
		return (0);
	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			words += 1;
		i++;
	}
	return (words);
}

static size_t	ft_len_next(char const *s, size_t pos, char c)
{
	size_t	i;

	i = 0;
	while (s[pos + i] != c && s[pos + i] != '\0')
		i++;
	return (i);
}

static	char	**ft_out(char **arr, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		free(arr[j]);
		j++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	size_t	pos;
	size_t	len;

	arr = malloc((ft_wc(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = -1;
	pos = 0;
	while (++i < ft_wc(s, c))
	{
		while (s[pos] == c)
			pos++;
		len = ft_len_next(s, pos, c);
		arr[i] = malloc((len + 1) * sizeof(char));
		if (!arr[i])
			return (ft_out(arr, i));
		arr[i] = ft_memmove(arr[i], s + pos, len);
		arr[i][len] = '\0';
		pos += len;
	}
	arr[i] = NULL;
	return (arr);
}
