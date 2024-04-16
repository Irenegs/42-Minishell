/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 09:29:54 by irgonzal          #+#    #+#             */
/*   Updated: 2024/04/16 22:05:18 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

t_word	*ft_lstlast(t_word *lst)
{
	t_word	a;

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
