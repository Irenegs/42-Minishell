/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 21:17:23 by irgonzal          #+#    #+#             */
/*   Updated: 2022/10/01 10:58:42 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && lst->content && del)
	{
		lst->next = NULL;
		del(lst->content);
		free(lst);
	}
}
