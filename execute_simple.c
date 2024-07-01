/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:56:55 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/01 18:49:47 by irene            ###   ########.fr       */
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

	childpid = fork();
	if (childpid == -1)
		exit(1);
	if (childpid == 0)
	{
		if (manage_simple_redirections(data->input, data->heredocs) != 0)
			exit(1);
		command = extract_command(data->input);
		if (!command)
			exit (1);
		run_command(command, data);
		ft_out(command);
		exit(1);
	}
	if (waitpid(childpid, &status, 0) != -1)
		return (WEXITSTATUS(status));
	return (0);
}
