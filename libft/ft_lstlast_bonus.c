/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 09:29:54 by irgonzal          #+#    #+#             */
/*   Updated: 2022/09/30 09:49:20 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	a;

	if (!lst)
		return (NULL);
	a = lst[0];
	if (a.next == NULL)
		return (lst);
	while (a.next->next != NULL)
	{
		a = *a.next;
	}
	return (a.next);
}
