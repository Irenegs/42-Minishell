/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:58:35 by pablgarc          #+#    #+#             */
/*   Updated: 2024/11/22 18:55:52 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

void	prompt(t_mix *data)
{
	int	copy_stdin;

	copy_stdin = dup(STDIN_FILENO);
	//ft_signals_start();
	while (1)
	{
		dup2(copy_stdin, 0);
		ft_signals_start();
		//printf("Exit status antes: %d\n", g_exit_status);
		data->input = readline("\033[0;32mMinishell:\033[0m ");
		//printf("Exit status tras readline: %d\n", g_exit_status);
		
		if (data->input == NULL)
		{
			printf("\n");
			break ;
		}
		if (*data->input)
			add_history(data->input);
		if (*data->input != '\0')
		{
			ft_signals_running();
			parse_and_execute(data);
		}
		else
			data->exit_status = g_exit_status;
		free(data->input);
	}
	close(copy_stdin);
}

int	main(int argc, char **argv, char **envp)
{
	t_mix	data;

	if (argc != 1 || !argv)
		return (1);
	ft_init_mix(&data, envp);
	prompt(&data);
	ft_out(data.m_env);
	return (0);
}
