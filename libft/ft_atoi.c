/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:38:00 by irgonzal          #+#    #+#             */
/*   Updated: 2022/10/01 10:43:58 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(char c)
{
	if (c == 32 || (c < 14 && c > 8))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	long int	n;
	int			s;

	i = 0;
	s = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			s = -1;
		i++;
	}
	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		if (n > 2147483647 && s == 1)
			return (-1);
		if (n > 2147483648 && s == -1)
			return (0);
		i++;
	}
	return ((int )(n * s));
}
