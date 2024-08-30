/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:06:33 by irgonzal          #+#    #+#             */
/*   Updated: 2024/08/30 20:04:05 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_quote(char c)
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
	else if (*quotes == 0 && (c == '\'' || c == '"'))
		*quotes = c;
}

char	**ft_out(char **arr)
{
	int	j;

	j = 0;
	while (arr[j])
	{
		free(arr[j]);
		j++;
	}
	free(arr);
	return (NULL);
}
