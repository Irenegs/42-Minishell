/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:50:11 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/11 20:33:50 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_heredocs_texts(char **heredocs, int pipes, char *s, t_mix *data)
{
	int		p;
	char	*subs;
	int		n_heredocs;
	int		n;

	p = 0;
	while (p <= pipes)
	{
		subs = extract_pipe(s, p);
		if (!subs)
			return (1);
		n_heredocs = number_of_heredocs(subs);
		n = 0;
		while (n < n_heredocs)
		{
			if (write_hd_file(subs + locate_n_hd(subs, n), heredocs[p], data) != 0)
				return (-1);
			n++;
		}
		if (n_heredocs == 0)
			heredocs[p] = NULL;
		p++;
	}
	return (0);
}

static int	get_heredocs_filenames(char **heredocs, int pipes)
{
	int		n;
	char	*number;

	n = 0;
	if (!heredocs)
		return (1);
	while (n <= pipes)
	{
		number = ft_itoa(n);
		if (!number)
			return (1);
		heredocs[n] = ft_strjoin("/tmp/.hdfile_", number);
		free(number);
		if (!heredocs[n])
			return (1);
		n++;
	}
	return (0);
}

int	get_heredocs(char **heredocs, t_mix *data, int pipes)
{
	if (get_heredocs_filenames(heredocs, pipes) != 0)
		return (-1);
	return (get_heredocs_texts(heredocs, pipes, data->input, data));
}

void	clean_and_free_heredocs(char **heredocs, int pipes)
{
	int	p;

	p = 0;
	while (p <= pipes && heredocs)
	{
		if (heredocs[p] != NULL)
		{
			if (access(heredocs[p], F_OK) != -1)
				unlink(heredocs[p]);
			free(heredocs[p]);
		}
		p++;
	}
	free(heredocs);
}
