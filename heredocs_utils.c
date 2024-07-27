/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:57:55 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/27 20:15:21 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	number_of_heredocs(char *subs)
{
	int	i;
	int	hd;
	int	quotes;

	if (!subs)
		return (-1);
	i = 0;
	hd = 0;
	quotes = 0;
	while (subs[i] != '\0')
	{
		if (subs[i] == '<' && subs[i + 1] == '<' && quotes == 0)
		{
			i++;
			hd++;
		}
		if (subs[i] == quotes && quotes != 0)
			quotes = 0;
		else if (quotes == 0 && (subs[i] == '\'' || subs[i] == '"'))
			quotes = subs[i];
		i++;
	}
	return (hd);
}

int	locate_n_hd(char *subs, int n)
{
	int	pos;
	int	hd_counter;

	if (!subs)
		return (-1);
	pos = 0;
	hd_counter = 0;
	while (subs[pos] != '\0')
	{
		if (subs[pos] == '<' && subs[pos + 1] == '<')
		{
			if (hd_counter == n)
				return (pos);
			pos++;
			hd_counter++;
		}
		pos++;
	}
	return (-1);
}
