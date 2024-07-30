/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:28:32 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/30 20:07:58 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*c;
	unsigned char	*d;

	if (n == 0)
		return (0);
	i = 0;
	c = (unsigned char *)s1;
	d = (unsigned char *)s2;
	while (c[i] == d[i] && i < n - 1)
	{
		i++;
	}
	return (c[i] - d[i]);
}
