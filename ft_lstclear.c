/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 21:29:50 by irgonzal          #+#    #+#             */
/*   Updated: 2024/04/16 22:05:04 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

void	ft_lstclear(t_word **lst, void (*del)(void *))
{
	t_word	*a;
	t_word	*b;

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
