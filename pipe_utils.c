/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 18:45:40 by irene             #+#    #+#             */
/*   Updated: 2024/06/29 18:28:30 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_multiple_pipes(int p, int pipes, int *fd)
{
	int	i;

	i = 0;
	while (i <= 2 * p)
	{
		if (i != 2 * p - 2 && i != 2 * pipes)
			close(fd[i]);
		i++;
	}
}

void	close_pipes(int pipes, int *fd)
{
	int	i;

	i = 0;
	while (i < pipes)
	{
		close(fd[2 * i]);
		close(fd[2 * i + 1]);
		i++;
	}
}

int	pipe_abortion(int *fd)
{
	if (fd != NULL)
		free(fd);
	return (1);
}
