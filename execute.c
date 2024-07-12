/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:09:28 by irgonzal          #+#    #+#             */
/*   Updated: 2024/07/11 20:26:04 by irene            ###   ########.fr       */
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

	manage_multiple_pipes(p, data->pipes, data->pipesfd);
	subs = extract_pipe(data->input, p);
	if (!subs)
		exit (1);
	if (manage_redirections(p, data, subs) != 0)
		exit(1);
	command = extract_command(subs, data);
	if (!command)
	{
		free(subs);
		exit (1);
	}
	run_command(command, data);
	free(subs);//llegará a aquí cuando es builtin?
	ft_out(command);
	exit (0);
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
		pipe(data->pipesfd + 2 * p);
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
	last_status = WEXITSTATUS(status);
	while (wait(&status) > 0)
		printf("Exit: %d\n", status);
	return (last_status);
}

int	execute(t_mix *data)
{
	int		ret_value;

	ret_value = 0;
	if (data->pipes != 0)
		data->heredocs = malloc(data->pipes * sizeof(char *));
	else
		data->heredocs = malloc(1 * sizeof(char *));
	if (!data->heredocs)
		ret_value = 1;
	if (ret_value == 0 && get_heredocs(data->heredocs, data, data->pipes) == 0)
	{
		data->pipesfd = malloc((data->pipes - 1) * 2 * sizeof(int));
		if (data->pipes != 0 && data->pipesfd)
		{
			ret_value = execute_several_pipes(data);
			free(data->pipesfd);
		}
		else if (data->pipes == 0)
			ret_value = execute_only_child(data);
		clean_and_free_heredocs(data->heredocs, data->pipes);
	}
	return (ret_value);
}

void	parse_and_execute(t_mix *data)
{
	if (!data || !data->input || ft_strlen(data->input) == 0)
		return ;
	data->pipes = parser(data->input);
	if (data->pipes == -1)
	{
		printf("Parse error\n");
		data->exit_status = 2;
		return ;
	}
	data->exit_status = execute(data);
	printf("echo $?:%d\n", data->exit_status);
}

/*
int	execute(t_mix *data, int pipes)
{
	int		*fd;
	char	**heredocs;
	int		ret_value;

	if (pipes != 0)
		heredocs = malloc(pipes * sizeof(char*));
	else 
		heredocs = malloc(1 * sizeof(char*));
	if (!heredocs)
		return (1);
	if (get_heredocs(heredocs, data, pipes) != 0)
	{
		free(heredocs);
		return (1);
	}
	if (pipes != 0)
	{
		fd = malloc((pipes - 1) * 2 * sizeof(int));
		if (!fd)
		{
			free(heredocs);
			return (1);
		}
		ret_value = execute_several_pipes(data, pipes, fd, heredocs);
		free(fd);
	}
	else
		ret_value = execute_only_child(data, heredocs);
	clean_and_free_heredocs(heredocs, pipes);
	return (ret_value);
}
*/