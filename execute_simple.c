/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:56:55 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/20 18:39:43 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	status_treatment(int *status)
{
	if (WIFEXITED(*status) != 0)
		return (WEXITSTATUS(*status));
	if (WIFSIGNALED(*status) != 0)
	{
		if (WTERMSIG(*status) == 2)
			return (130);
		if (WTERMSIG(*status) == 3)
			return (131);
		return (WTERMSIG(*status));
	}
	return (0);
}

static int	manage_simple_redirections(t_mix *data)
{
	int		input;
	int		output;

	input = extract_input(data->input, data, -1);
	if (input > 0)
		dup2(input, STDIN_FILENO);
	if (input == -2)
		return (1);
	output = extract_output(data->input, data);
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
		if (manage_simple_redirections(data) != 0)
			exit(1);
		command = extract_command(data->input, data);
		if (!command)
			exit (1);
		status = run_command(command, data);
		ft_out(command);
		exit(status);
	}
	if (waitpid(childpid, &status, 0) != -1)
		return (status_treatment(&status));
	return (0);
}
