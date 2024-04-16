/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:48:49 by irgonzal          #+#    #+#             */
/*   Updated: 2024/04/16 22:05:01 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include	"minishell.h"

void	ft_lstadd_front(t_word **lst, t_word *new)
{
	if (lst)
		new->next = *lst;
	*lst = new;
}
