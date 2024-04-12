/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:55:35 by irgonzal          #+#    #+#             */
/*   Updated: 2022/09/29 14:54:23 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	l1;
	unsigned int	len;
	char			*str;

	l1 = 0;
	if (s1)
		l1 = ft_strlen(s1);
	len = l1;
	if (s2)
		len += ft_strlen(s2);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memmove(str, s1, l1);
	ft_memmove(str + l1, s2, len - l1);
	str[len] = '\0';
	return (str);
}
