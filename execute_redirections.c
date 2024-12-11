/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 23:20:45 by irene             #+#    #+#             */
/*   Updated: 2024/12/11 23:23:18 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_redirections(int p, t_mix *data, char *subs)
{
	int		input;
	int		output;

	input = extract_input(subs, data, p);
	if (input == -2)
		return (1);
	else if (input > 0)
		dup2(input, STDIN_FILENO);
	else if (p > 0)
		dup2(data->pipesfd[2 * (p - 1)], STDIN_FILENO);
	output = extract_output(subs, data);
	if (output == -2)
		return (1);
	if (p != data->pipes)
		dup2(data->pipesfd[2 * p + 1], STDOUT_FILENO);
	if (output > 0)
		dup2(output, STDOUT_FILENO);
	return (0);
}
