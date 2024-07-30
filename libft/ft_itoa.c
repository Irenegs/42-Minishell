/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:05:13 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/30 20:07:41 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbrlen(long long int n)
{
	int	l;

	l = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		l++;
		n /= 10;
	}
	return (l);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

char	*ft_itoa(int n)
{
	int		l;
	char	*res;

	l = nbrlen(n);
	res = malloc((l + 1 + (n < 0)) * sizeof(char));
	if (!res)
		return (NULL);
	res[l + (n < 0)] = '\0';
	if (n < 0)
		res[0] = '-';
	while (--l >= 0)
	{
		res[l + (n < 0)] = ft_abs(n % 10) + '0';
		n = n / 10;
	}
	return (res);
}
