/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:26:31 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/30 20:10:14 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (*(haystack + i) != '\0' && i < len)
	{
		if (*(haystack + i) == *needle)
		{
			j = 1;
			while (*(haystack + i + j) != '\0' && *(needle + j) != '\0'
				&& *(haystack + i + j) == *(needle + j) && i + j < len)
				j++;
			if (*(needle + j) == '\0')
			{
				return ((char *) haystack + i);
			}
		}
		i++;
	}
	return (0);
}
