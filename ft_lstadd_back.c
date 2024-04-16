/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 09:50:18 by irgonzal          #+#    #+#             */
/*   Updated: 2024/04/16 22:04:54 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

void	ft_lstadd_back(t_word **lst, t_word *new)
{
	t_word	*a;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	a = *lst;
	while (a->next != NULL)
		a = a->next;
	a->next = new;
}
