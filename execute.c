/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:09:28 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/27 20:20:52 by irgonzal         ###   ########.fr       */
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

int	extract_pipe_and_execute(int p, t_mix *data)
{
	char	*subs;
	char	**command;
	int		ret_value;

	manage_multiple_pipes(p, data->pipes, data->pipesfd);
	subs = extract_pipe(data->input, p);
	if (!subs)
		exit(write_error_int(1, 1));
	if (manage_redirections(p, data, subs) != 0)
		exit(1);
	command = extract_command(subs, data);
	if (!command)
	{
		free(subs);
		exit (1);
	}
	ret_value = run_command(command, data);
	free(subs);
	ft_out(command);
	exit(ret_value);
}

int	execute_several_pipes(t_mix *data)
{
	int		p;
	int		childpid;
	int		status;
	int		last_status;

	p = 0;
	while (p <= data->pipes)
	{
		if (p != data->pipes && pipe(data->pipesfd + 2 * p) == -1)
			return (1);
		childpid = fork();
		if (childpid == -1)
			return (1);
		if (childpid == 0)
			extract_pipe_and_execute(p, data);
		p++;
	}
	close_pipes(data->pipes, data->pipesfd);
	if (waitpid(childpid, &status, 0) == -1)
		exit(1);
	last_status = status_treatment(&status);
	while (wait(&status) > 0)
		;
	return (last_status);
}

int	execute(t_mix *data)
{
	int		ret_value;

	ret_value = 0;
	data->heredocs = malloc((data->pipes + 2) * sizeof(char *));
	if (!data->heredocs)
		ret_value = write_error_int(1, 1);
	if (ret_value == 0 && get_heredocs(data) == 0)
	{
		if (data->pipes != 0)
			data->pipesfd = malloc((data->pipes) * 2 * sizeof(int));
		if (data->pipes != 0 && data->pipesfd && g_exit_status != 130)
		{
			ret_value = execute_several_pipes(data);
			free(data->pipesfd);
		}
		else if (data->pipes == 0 && g_exit_status != 130)
			ret_value = execute_zero_pipes(data);
		else if (g_exit_status != 130)
			ret_value = write_error_int(1, 1);
	}
	else
		ret_value = 1;
	clean_and_free_heredocs(data->heredocs, data->pipes);
	return (ret_value);
}

void	parse_and_execute(t_mix *data)
{
	if (!data || !data->input || ft_strlen(data->input) == 0)
		return ;
	g_exit_status = 0;
	data->pipes = parser(data->input);
	if (data->pipes == -1)
	{
		printf("Parse error\n");//cambiar por write en 2
		data->exit_status = 2;
		return ;
	}
	data->exit_status = execute(data);
	//printf("Echo $?:%d\n", data->exit_status);
}
