/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:09:28 by irgonzal          #+#    #+#             */
/*   Updated: 2024/06/23 18:11:00 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_input_output_command(int p, int *fd, char *subs, int pipes)
{
	int		input;
	int		output;

	input = extract_input(subs);
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
	
	return (1);
}

int	execute_only_child(t_mix *data)
{
	int		childpid;
	char	**command;

	childpid = fork();
	if (childpid == -1)
		exit(1);
	if (childpid == 0)
	{
		manage_input_output_command(-1, NULL, data->input, 0);
		command = extract_command(data->input);
		if (!command)
			return (1);
		run_command(command, data);
		//if (run_command(command, data) != 0)
		//	ft_out(command);
		return (-1);
	}
	if (waitpid(-1, &childpid, 0) != -1)
	{
		printf("exit!\n");
		return(childpid);
	}
	return (0);
}

int	execute(t_mix *data, int pipes)
{
	int		p;
	int		*fd;
	char	*subs;
	int		childpid;
	int		status;
	char	**command;

	p = 0;
	fd = malloc((pipes - 1) * 2 * sizeof(int));
	if (!fd)
		return (1);
	while (p <= pipes)
	{
		if (p != pipes)
			pipe(fd + 2 * p);
		childpid = fork();
		if (childpid == -1)
			break ;
		if (childpid == 0)
		{
			manage_multiple_pipes(p, pipes, fd);
			subs = extract_pipe(data->input, p);
			if (!subs)
				break ;
			manage_input_output_command(p, fd, subs, pipes);
			command = extract_command(subs);
			if (!command)
				return (1);
			run_command(command, data);
			//if (run_command(command, data) != 0)
			//	ft_out(command);
		}
		p++;
	}
	close_pipes(pipes, fd);
	free(fd);
	while (wait(&status) > 0)
		printf("Exit: %d\n", status);
	return (0);
}

void	parse_and_execute(t_mix *data)
{
	int	pipes;

	if ( !data || !data->input || ft_strlen(data->input) == 0)
		return ;
	pipes = parser(data->input);
	if (pipes == -1)
		printf("Parse error\n");
	else if (pipes == 0)
		execute_only_child(data);
	else if (pipes > 0)
		execute(data, pipes);
	if (access(".tmpfile", F_OK) != -1)
		unlink(".tmpfile");
}
