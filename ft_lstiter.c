/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 21:53:22 by irgonzal          #+#    #+#             */
/*   Updated: 2024/04/16 22:05:13 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

void	ft_lstiter(t_word *lst, void (*f)(void *))
{
	t_word	*a;

	a = lst;
	while (a != NULL)
	{
		f(a->content);
		a = a->next;
	}
}
