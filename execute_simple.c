/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:56:55 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/27 20:12:57 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	status_treatment(int *status)
{
	if (WIFEXITED(*status) != 0)
		return (WEXITSTATUS(*status));
	if (WIFSIGNALED(*status) != 0)
		return (WTERMSIG(*status) + 128);
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

static int	execute_only_child(t_mix *data, char **command)
{
	int		childpid;
	int		status;

	childpid = fork();
	if (childpid == -1)
	{
		perror(NULL);
		return (1);
	}
	if (childpid == 0)
	{
		if (manage_simple_redirections(data) != 0)
			exit(1);
		status = run_command(command, data);
		exit(status);
	}
	if (waitpid(childpid, &status, 0) != -1)
		return (status_treatment(&status));
	return (0);
}

int	execute_zero_pipes(t_mix *data)
{
	char	**command;
	int		status;

	command = extract_command(data->input, data);
	if (!command)
		return (write_error_int(1, 1));
	if (is_special_builtin(command[0]) == 1)
		status = execute_builtin(data, command);
	else
		status = execute_only_child(data, command);
	ft_out(command);
	return (status);
}
