/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:27:17 by irene             #+#    #+#             */
/*   Updated: 2024/12/01 19:06:13 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_char(char **result, char *orig, int pos)
{
	char	*new;
	size_t	len_result;

	if (!result || !*result || !orig || pos < 0
		|| (size_t)pos >= ft_strlen(orig))
		return ;
	len_result = ft_strlen(*result);
	new = malloc((len_result + 2) * sizeof(char));
	if (!new)
	{
		free(*result);
		*result = NULL;
		write_error_null(1);
		return ;
	}
	ft_memmove(new, *result, len_result);
	new[len_result] = orig[pos];
	new[len_result + 1] = '\0';
	free(*result);
	*result = new;
}
