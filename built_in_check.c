/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:31:25 by pablo             #+#    #+#             */
/*   Updated: 2024/05/23 23:00:52 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else
		return (0);
}

int	choose_and_execute_builtin(t_mix *data, char **command)
{
	if (ft_strcmp(command[0], "echo") == 0)
		return (ft_echo(command));
	else if (ft_strcmp(command[0], "cd") == 0)
		return (ft_cd(command, data));
	else if (ft_strcmp(command[0], "pwd") == 0)
		return (ft_pwd(data));
	else if (ft_strcmp(command[0], "exit") == 0)
		return (ft_exit(command, data));
	else if (ft_strcmp(command[0], "export") == 0)
		return (ft_export(data, command));
	else if (ft_strcmp(command[0], "unset") == 0)
		return (ft_unset(data, command));
	else if (ft_strcmp(command[0], "env") == 0)
		return (ft_env(data));
	return (1);
}

static int	redirect_input(t_mix *data, int *input, int *stdin_copy)
{
	*input = extract_input(data->input, data, -1);
	if (*input > 0)
	{
		*stdin_copy = dup(0);
		dup2(*input, STDIN_FILENO);
	}
	if (*input == -2)
		return (1);
	return (0);
}

static int	redirect_output(t_mix *data, int *output, int *stdout_copy)
{
	*output = extract_output(data->input, data);
	if (*output > 0)
	{
		*stdout_copy = dup(1);
		dup2(*output, STDOUT_FILENO);
	}
	if (*output == -2)
		return (1);
	return (0);
}

int	execute_builtin(t_mix *data, char **command)
{
	int input;
	int output;
	int return_value;
	int stdin_copy;
	int	stdout_copy;

	if (redirect_input(data, &input, &stdin_copy) != 0)
		return (1);
	if (redirect_output(data, &output, &stdout_copy) != 0)
		return (1);
	return_value = choose_and_execute_builtin(data, command);
	if (input > 0)
	{
		close(input);
		dup2(stdin_copy, 0);
	}
	if (output > 0)
	{
		close(output);
		dup2(stdout_copy, 1);
	}
	return (return_value);
}
