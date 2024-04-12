/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:46:47 by irgonzal          #+#    #+#             */
/*   Updated: 2022/10/10 12:54:19 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

static int	ft_charinset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0' && set[i] != c)
		i++;
	return (set[i] == c);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		i;
	size_t	l;

	if (!s1)
		return (NULL);
	l = ft_strlen(s1);
	while (l != 0 && ft_charinset(s1[l - 1], set) == 1)
		l--;
	i = 0;
	if (l != 0)
	{
		while (ft_charinset(s1[i++], set) == 1)
			l--;
	}
	res = malloc((l + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res = ft_memmove(res, s1 + i - 1, l + 1);
	res[l] = '\0';
	return (res);
}
