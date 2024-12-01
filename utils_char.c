/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:06:33 by irgonzal          #+#    #+#             */
/*   Updated: 2024/12/01 18:58:45 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return ((int) c);
	return (0);
}

int	is_space(char c)
{
	if (c == 32 || (c < 14 && c > 8) || c == '\0')
		return (1);
	return (0);
}

int	is_separator(char c)
{
	return ((c != ' ' && c != '<' && c != '>' && c != '|'));
}

void	manage_quotes(int *quotes, char c)
{
	if (c == *quotes && *quotes != 0)
		*quotes = 0;
	else if (*quotes == 0 && is_quote(c) != 0)
		*quotes = c;
}

char	**free_partial_array(char **array, int filled)
{
	int	i;

	i = 0;
	if (!array)
		return (NULL);
	while (i < filled)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}
