/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:16:03 by irgonzal          #+#    #+#             */
/*   Updated: 2024/04/16 22:05:28 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

int	ft_lstsize(t_word *lst)
{
	int		i;
	t_word	a;

	if (!lst)
		return (0);
	a = lst[0];
	i = 1;
	while (a.next != NULL)
	{
		a = *a.next;
		i++;
	}
	return (i);
}
