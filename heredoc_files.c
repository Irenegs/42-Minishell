/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:50:11 by irgonzal          #+#    #+#             */
/*   Updated: 2024/08/26 19:00:35 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	ft_free_sub(char *subs)
{
	free(subs);
	return (-1);
}

static int	get_heredocs_texts(int pipes, char *s, t_mix *data)
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
			return (write_error_int(1, 1));
		n_heredocs = number_of_heredocs(subs);
		n = 0;
		while (n < n_heredocs)
		{
			if (write_hd_file(subs + locate_n_hd(subs, n), p, data) != 0)
				return (ft_free_sub(subs));
			n++;
		}
		free(subs);
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
		{
			heredocs[n] = NULL;
			return (1);
		}
		heredocs[n] = ft_strjoin("/tmp/.hdfile_", number);
		free(number);
		if (!heredocs[n])
			return (1);
		n++;
	}
	heredocs[pipes + 1] = NULL;
	return (0);
}

int	get_heredocs(t_mix *data)
{
	if (get_heredocs_filenames(data->heredocs, data->pipes) != 0)
		return (1);
	return (get_heredocs_texts(data->pipes, data->input, data));
}

void	clean_and_free_heredocs(char **heredocs, int pipes)
{
	int	p;

	p = 0;
	while (p <= pipes && heredocs && heredocs[p] != NULL)
	{
		if (access(heredocs[p], F_OK) != -1)
			unlink(heredocs[p]);
		free(heredocs[p]);
		p++;
	}
	free(heredocs);
}
