/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:53:25 by irgonzal          #+#    #+#             */
/*   Updated: 2022/09/29 09:50:07 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

char	*ft_strdup(char *src)
{
	unsigned int	i;
	unsigned int	len;
	char			*p;

	len = ft_strlen(src);
	p = malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	while (i < len)
	{
		*(p + i) = *(src + i);
		i++;
	}
	*(p + i) = '\0';
	return (p);
}
