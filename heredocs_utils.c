/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:57:55 by irgonzal          #+#    #+#             */
/*   Updated: 2024/06/28 19:03:37 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	number_of_heredocs(char *subs)
{
	int	i;
	int	hd;

	if (!subs)
		return (-1);
	i = 0;
	hd = 0;
	while (subs[i] != '\0')
	{
		if (subs[i] == '<' && subs[i + 1] == '<')
		{
			i++;
			hd++;
		}
		i++;
	}
	return (hd);
}

int	locate_nth_heredoc(char *subs, int n)
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
