/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:16:03 by irgonzal          #+#    #+#             */
/*   Updated: 2022/09/30 09:24:37 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	a;

	if (!lst)
		return (0);
	a = lst[0];
	i = 1;
	while (a.next != NULL)
	{
		a = *a.next;
		i++;
	}
	return (i);
}
