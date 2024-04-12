/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:48:49 by irgonzal          #+#    #+#             */
/*   Updated: 2022/09/29 16:14:30 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include	"libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst)
		new->next = *lst;
	*lst = new;
}
