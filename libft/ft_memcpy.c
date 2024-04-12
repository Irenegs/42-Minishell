/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:04:03 by irgonzal          #+#    #+#             */
/*   Updated: 2022/09/23 14:30:44 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)dst;
	p2 = (unsigned char *)src;
	if ((!dst && !src) || n == 0)
		return (dst);
	i = 0;
	while (i < n)
	{
		p1[i] = p2[i];
		i++;
	}
	return (dst);
}
