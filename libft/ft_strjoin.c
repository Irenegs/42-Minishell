/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:55:35 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/30 20:09:46 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
