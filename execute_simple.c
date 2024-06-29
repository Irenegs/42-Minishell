/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:56:55 by irgonzal          #+#    #+#             */
/*   Updated: 2024/06/29 18:59:55 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	manage_simple_redirections(char *input_str, char **heredocs)
{
	int		input;
	int		output;

	input = extract_input(input_str, heredocs, -1);
	if (input > 0)
		dup2(input, STDIN_FILENO);
	if (input == -2)
		return (1);
	output = extract_output(input_str);
	if (output > 0)
		dup2(output, STDOUT_FILENO);
	if (output == -2)
		return (1);
	return (0);
}

int	execute_only_child(t_mix *data)
{
	int		childpid;
	char	**command;
	int		status;
	char	**heredocs;

	heredocs = malloc(1 * sizeof(char*));
	if (!heredocs)
		return (1);
	if (get_heredocs(heredocs, data, 0) != 0)
	{
		free(heredocs);
		return (1);
	}
	childpid = fork();
	if (childpid == -1)
		exit(1);
	if (childpid == 0)
	{
		if (manage_simple_redirections(data->input, heredocs) != 0)
			exit(errno);
		command = extract_command(data->input);
		if (!command)
			return (1);
		run_command(command, data);
		exit(0);
	}
	if (waitpid(-1, &status, 0) != -1)
	{
		clean_and_free_heredocs(heredocs, 0);
		return (status);
	}
	clean_and_free_heredocs(heredocs, 0);
	return (0);
}
