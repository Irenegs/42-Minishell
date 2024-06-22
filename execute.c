/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:56:56 by irene             #+#    #+#             */
/*   Updated: 2024/06/22 22:17:48 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_input_output_command(int p, int *fd, char *subs, int pipes)
{
	int		input;
	int		output;
	char	**command;

	input = extract_input(subs);
	if (input > 0)
		dup2(input, STDIN_FILENO);
	else if (p != -1)
	{
		dup2(fd[2 * (p - 1)], STDIN_FILENO);
		close(fd[2 * p - 1]);
	}
	if (p != pipes)
		dup2(fd[2 * p + 1], STDOUT_FILENO);
	output = extract_output(subs);
	if (output > 0)
		dup2(output, STDOUT_FILENO);
	command = extract_command(subs);
	if (!command)
		return (1);
	run_command(command);
	if (run_command(command) != 0)
		ft_out(command);
	return (1);
}

int	execute_only_child(char *s)
{
	int		childpid;

	childpid = fork();
	if (childpid == -1)
		exit(1);
	if (childpid == 0)
	{
		manage_input_output_command(-1, NULL, s, 0);
		return (-1);
	}
	if (waitpid(-1, &childpid, 0) != -1)
		printf("exit!\n");
	return (0);
}

int	execute(char *s, int pipes)
{
	int		p;
	int		*fd;
	char	*subs;
	int		childpid;
	int		status;

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
			subs = extract_pipe(s, p);
			if (!subs)
				break ;
			manage_input_output_command(p, fd, subs, pipes);
		}
		p++;
	}
	close_pipes(pipes, fd);
	free(fd);
	while (wait(&status) > 0)
		printf("Exit: %d\n", status);
	return (0);
}

void	parse_and_execute(char *s)
{
	int	pipes;

	if (!s || ft_strlen(s) == 0)
		return ;
	pipes = parser(s);
	if (pipes == -1)
		printf("Parse error\n");
	else if (pipes == 0)
		execute_only_child(s);
	else if (pipes > 0)
		execute(s, pipes);
	if (access(".tmpfile", F_OK) != -1)
		unlink(".tmpfile");
}
