/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:21:56 by irgonzal          #+#    #+#             */
/*   Updated: 2022/09/26 16:18:15 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	sdst;

	sdst = 0;
	while (src[sdst] != '\0' && sdst + 1 < dstsize)
	{
		dst[sdst] = src[sdst];
		sdst++;
	}
	if (dstsize != 0)
		dst[sdst] = '\0';
	while (src[sdst] != '\0')
		sdst++;
	return (sdst);
}
