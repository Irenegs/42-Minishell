/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:59:02 by irgonzal          #+#    #+#             */
/*   Updated: 2022/10/10 13:35:33 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

static t_list	*ft_out(t_list *lst, void (*del)(void *))
{
	ft_lstclear(&lst, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*a;
	t_list	*b;
	void	*c;

	if (!lst || !f)
		return (NULL);
	c = f(lst->content);
	res = ft_lstnew(c);
	if (!res)
		return (NULL);
	a = lst->next;
	while (a != NULL)
	{
		c = f(a->content);
		b = ft_lstnew(c);
		if (!b)
			return (ft_out(res, del));
		ft_lstadd_back(&res, b);
		a = a->next;
	}
	return (res);
}
