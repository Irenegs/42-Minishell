/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:29:41 by irgonzal          #+#    #+#             */
/*   Updated: 2022/09/27 16:59:54 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*p1;
	const char	*p2;

	if (dst == 0 && src == 0)
		return (dst);
	p1 = dst;
	p2 = src;
	if (p1 < p2 || (long unsigned int)(p1 - p2) > n)
		return (ft_memcpy(dst, src, n));
	i = n;
	while (i > 0)
	{
		*(p1 + i - 1) = *(p2 + i - 1);
		i--;
	}
	return (dst);
}
