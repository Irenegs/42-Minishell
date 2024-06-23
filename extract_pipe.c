/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:19:22 by irgonzal          #+#    #+#             */
/*   Updated: 2024/06/23 16:32:31 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	locate_pipe_init(char *s, int pipe)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (p < pipe)
	{
		if (s[i] == '|')
			p++;
		i++;
	}
	while (s[i] == '|' || is_space(s[i]) == 1)
		i++;
	return (i);
}

static int	pipe_len(char *s, int pos)
{
	int	len;

	len = 0;
	while (s[pos + len] != '|' && s[pos + len] != '\0')
		len++;
	while (is_space(s[pos + len]) == 1 || s[pos + len] == '|')
		len--;
	return (++len);
}

char	*extract_pipe(char *s, int pipe)
{
	int	pos;
	int	len;

	pos = 0;
	len = 0;
	pos = locate_pipe_init(s, pipe);
	len = pipe_len(s, pos);
	return (ft_substr(s, pos, len));
}
