/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 18:45:40 by irene             #+#    #+#             */
/*   Updated: 2024/07/11 20:31:08 by irene            ###   ########.fr       */
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
