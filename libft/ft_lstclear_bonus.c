/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 21:29:50 by irgonzal          #+#    #+#             */
/*   Updated: 2022/10/01 17:49:52 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*a;
	t_list	*b;

	if (!del || !lst || !*lst)
		return ;
	a = *lst;
	b = a->next;
	while (b != NULL)
	{
		ft_lstdelone(a, del);
		a = b;
		b = b->next;
	}
	ft_lstdelone(a, del);
	*lst = NULL;
}
