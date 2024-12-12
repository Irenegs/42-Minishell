/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:56:15 by irene             #+#    #+#             */
/*   Updated: 2024/12/12 21:58:56 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	variables_to_expand(char *str)
{
	int	quotes;
	int	i;

	quotes = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && quotes != '\'')
			return (1);
		manage_quotes(&quotes, str[i]);
		i++;
	}
	return (0);
}
