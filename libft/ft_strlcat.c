/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:38:42 by irgonzal          #+#    #+#             */
/*   Updated: 2022/09/29 09:45:49 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	sdst;
	unsigned int	ssum;

	if (dst == 0 && dstsize == 0)
		return (ft_strlen(src));
	sdst = ft_strlen(dst);
	ssum = sdst;
	while (src[ssum - sdst] != '\0' && (ssum + 1) < dstsize)
	{
		dst[ssum] = src[ssum - sdst];
		ssum++;
	}
	if (sdst < dstsize)
		dst[ssum] = '\0';
	while (src[ssum - sdst] != '\0')
		ssum++;
	if (sdst > dstsize)
		return (ssum - sdst + dstsize);
	return (ssum);
}
