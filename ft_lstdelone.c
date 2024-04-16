/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 21:17:23 by irgonzal          #+#    #+#             */
/*   Updated: 2024/04/16 22:05:08 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

void	ft_lstdelone(t_word *lst, void (*del)(void *))
{
	if (lst && lst->content && del)
	{
		lst->next = NULL;
		del(lst->content);
		free(lst);
	}
}
