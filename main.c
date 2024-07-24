/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/24 19:43:35 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	g_exit_status = 0;

void	prompt(t_mix *data)
{
	int copy_stdin;

	copy_stdin = dup(STDIN_FILENO);
	ft_signals_start();
	while (1)
	{
		dup2(copy_stdin, 0);
		ft_signals_start();
		data->input = readline("\033[0;32mMinishell:\033[0m ");
		if (data->input == NULL) //esto seria la señal de CRTL +D
		{
			printf("\n");
			break ;
		}
		ft_signals_running();
		if (*data->input)
			add_history(data->input);
		if (*data->input != '\0')
			parse_and_execute(data);
		free(data->input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mix	data;

	if (argc != 1 || !argv)
		return (1);
	ft_init_mix(&data, envp);
	prompt(&data);
	ft_free_env(data.m_env);
	return (0);
}

/*
void	prompt(void)
{
	char *s;

	s = readline("Minishell:");
	while (s)
	{
		//printf("String:\n%s\n", s);
		add_history(s);
		parse_and_execute(s);
		free(s);
		s = readline("Minishell:");
	}
	//rl_clear_history();
}

void signal_handler(int signum)
{
	if (signum == SIGQUIT)
		printf("Minishell:");//Esto no funciona bien
	else if (signum == SIGINT)
		printf("^CMinishell:");//No vuelve a la terminal
}

void show_leaks(void)
{
	system("leaks minishell");
}
*/