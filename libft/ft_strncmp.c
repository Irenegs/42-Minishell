/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:31:08 by irgonzal          #+#    #+#             */
/*   Updated: 2022/09/29 09:28:14 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	c;
	unsigned char	d;

	i = 0;
	if (n == 0)
		return (0);
	c = (unsigned char)s1[0];
	d = (unsigned char)s2[0];
	while (c == d && i < n - 1 && c != '\0' && d != '\0')
	{
		i++;
		c = (unsigned char)s1[i];
		d = (unsigned char)s2[i];
	}
	if (c == '\0' && d != '\0')
		return (-1);
	if (c != '\0' && d == '\0')
		return (1);
	return (c - d);
}
