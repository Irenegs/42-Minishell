/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:21:56 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/30 20:09:51 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
