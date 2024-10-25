/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:42:48 by irgonzal          #+#    #+#             */
/*   Updated: 2024/10/25 18:36:42 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	something_to_add(char *s, int pos)
{
	if (is_space(s[pos]) == 0 && s[pos] != '<' && s[pos] != '>'
		&& s[pos] != '|')
		return (1);
	return (0);
}
