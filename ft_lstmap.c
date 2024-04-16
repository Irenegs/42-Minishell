/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:59:02 by irgonzal          #+#    #+#             */
/*   Updated: 2024/04/16 22:05:22 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

static t_word	*ft_out(t_word *lst, void (*del)(void *))
{
	ft_lstclear(&lst, del);
	return (NULL);
}

t_word	*ft_lstmap(t_word *lst, void *(*f)(void *), void (*del)(void *))
{
	t_word	*res;
	t_word	*a;
	t_word	*b;
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
