/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:09:28 by irgonzal          #+#    #+#             */
/*   Updated: 2024/06/29 16:08:32 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_redirections(int p, int *fd, char *subs, int pipes, char **heredocs)
{
	int		input;
	int		output;

	input = extract_input(subs, heredocs, p);
	if (input > 0)
		dup2(input, STDIN_FILENO);
	else if (p != -1)
	{
		dup2(fd[2 * (p - 1)], STDIN_FILENO);
		close(fd[2 * p - 1]);
	}
	if (p != pipes && p != -1)
		dup2(fd[2 * p + 1], STDOUT_FILENO);
	output = extract_output(subs);
	if (output > 0)
		dup2(output, STDOUT_FILENO);
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
		manage_redirections(-1, NULL, data->input, 0, heredocs);
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

int	extract_pipe_and_execute(int p, int *fd, t_mix *data, int pipes, char **heredocs)
{
	char	*subs;
	char	**command;

	manage_multiple_pipes(p, pipes, fd);
	subs = extract_pipe(data->input, p);
	if (!subs)
		return (1);
	manage_redirections(p, fd, subs, pipes, heredocs);
	command = extract_command(subs);
	if (!command)
	{
		free(subs);
		return (1);
	}
	run_command(command, data);
	free(subs);//llegará a aquí cuando es builtin?
	ft_out(command);
	return (0);
}

int	execute_several_pipes(t_mix *data, int pipes, int *fd, char **heredocs)
{
	int		p;
	int		childpid;
	int		status;

	p = 0;
	while (p <= pipes)
	{
		if (p != pipes)
			pipe(fd + 2 * p);
		childpid = fork();
		if (childpid == -1)
			return (1);
		if (childpid == 0)
			extract_pipe_and_execute(p, fd, data, pipes, heredocs);
		p++;
	}
	close_pipes(pipes, fd);
	while (wait(&status) > 0)
		printf("Exit: %d\n", status);
	return (0);
}

int	execute(t_mix *data, int pipes)
{
	int		*fd;
	char	**heredocs;

	heredocs = malloc(pipes * sizeof(char*));
	if (!heredocs)
		return (1);
	if (get_heredocs(heredocs, data, pipes) != 0)
	{
		free(heredocs);
		return (1);
	}
	fd = malloc((pipes - 1) * 2 * sizeof(int));
	if (!fd)
		return (1);
	execute_several_pipes(data, pipes, fd, heredocs);
	free(fd);
	clean_and_free_heredocs(heredocs, pipes);
	return (0);
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
		//$? = 2
	}
	else if (pipes == 0)
		execute_only_child(data);
	else if (pipes > 0)
		execute(data, pipes);
}
