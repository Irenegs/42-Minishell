/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:09:50 by irgonzal          #+#    #+#             */
/*   Updated: 2022/09/29 15:46:27 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ptr;
	t_list	a;

	ptr = malloc(sizeof(t_list));
	if (!ptr)
		return (NULL);
	a.content = content;
	a.next = NULL;
	*ptr = a;
	return (ptr);
}
