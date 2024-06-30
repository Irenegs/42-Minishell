/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:09:28 by irgonzal          #+#    #+#             */
/*   Updated: 2024/06/30 19:15:25 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_redirections(int p, int *fd, char *subs, int pipes, char **heredocs)
{
	int		input;
	int		output;

	input = extract_input(subs, heredocs, p);
	if (input == -2)
		return (1);
	else if (input > 0)
		dup2(input, STDIN_FILENO);
	else if (p > 0)
		dup2(fd[2 * (p - 1)], STDIN_FILENO);
	output = extract_output(subs);
	if (output == -2)
		return (1);
	if (p != pipes)
		dup2(fd[2 * p + 1], STDOUT_FILENO);
	if (output > 0)
		dup2(output, STDOUT_FILENO);
	return (0);
}

int	extract_pipe_and_execute(int p, int *fd, t_mix *data, int pipes, char **heredocs)
{
	char	*subs;
	char	**command;

	manage_multiple_pipes(p, pipes, fd);
	subs = extract_pipe(data->input, p);
	if (!subs)
		exit (1);
	if (manage_redirections(p, fd, subs, pipes, heredocs) != 0)
		exit(1);
	command = extract_command(subs);
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

int	execute_several_pipes(t_mix *data, int pipes, int *fd, char **heredocs)
{
	int		p;
	int		childpid;
	int		status;
	int		last_childpid;
	int		last_status;

	p = 0;
	while (p <= pipes)
	{
		if (p != pipes)
		{
			pipe(fd + 2 * p);
			childpid = fork();
			if (childpid == -1)
				return (1);
			if (childpid == 0)
				extract_pipe_and_execute(p, fd, data, pipes, heredocs);
		}
		else
		{
			last_childpid = fork();
			if (last_childpid == -1)
				return (1);
			if (last_childpid == 0)
				extract_pipe_and_execute(p, fd, data, pipes, heredocs);
		}
		p++;
	}
	close_pipes(pipes, fd);
	while (waitpid(childpid, &status, 0) > 0)
	{
		printf("Exit: %d\n", status);
	}
	while (waitpid(last_childpid, &last_status, 0) > 0)
	{
		if (WIFEXITED(last_status) != 0)
			return (WEXITSTATUS(last_status));
	}
	return (0);
}

int	execute(t_mix *data, int pipes)
{
	int		*fd;
	char	**heredocs;
	int		ret_value;

	ret_value = 0;
	if (pipes != 0)
		heredocs = malloc(pipes * sizeof(char*));
	else 
		heredocs = malloc(1 * sizeof(char*));
	if (!heredocs)
		ret_value = 1;
	if (ret_value == 0 && get_heredocs(heredocs, data, pipes) == 0)
	{
		fd = malloc((pipes - 1) * 2 * sizeof(int));
		if (pipes != 0 && fd)
		{
			ret_value = execute_several_pipes(data, pipes, fd, heredocs);
			free(fd);
		}
		else if (pipes == 0)
			ret_value = execute_only_child(data, heredocs);
		clean_and_free_heredocs(heredocs, pipes);
	}
	return(ret_value);
}

void	parse_and_execute(t_mix *data)
{
	int	pipes;

	if (!data || !data->input || ft_strlen(data->input) == 0)
		return ;
	pipes = parser(data->input);
	if (pipes == -1)
	{
		printf("Parse error\n");
		data->exit_status = 2;
		return ;
	}
	data->exit_status = execute(data, pipes);
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