/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:09:50 by irgonzal          #+#    #+#             */
/*   Updated: 2024/04/16 22:06:14 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

t_word	*ft_lstnew(char *content, int func)
{
	t_word	*ptr;
	t_word	a;

	ptr = malloc(sizeof(t_word));
	if (!ptr)
		return (NULL);
	a.content = content;
	a.function = func;
	a.next = NULL;
	*ptr = a;
	return (ptr);
}
