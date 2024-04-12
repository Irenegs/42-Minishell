/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:49:48 by irgonzal          #+#    #+#             */
/*   Updated: 2022/10/01 17:33:59 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (count != 0 && size > SIZE_MAX / count)
		return (NULL);
	p = malloc(count * size);
	if (p != NULL)
		ft_bzero(p, count * size);
	return (p);
}
