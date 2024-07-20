/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:58:01 by irene             #+#    #+#             */
/*   Updated: 2024/07/20 18:51:16 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	global_signal = 0;

void	prompt(t_mix *data)
{
	while (1)
	{
		//ft_signals_new();
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

void show_leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_mix	data;
	atexit(show_leaks);
	if (argc != 1 || !argv)
		return (1);
	ft_init_mix(&data, envp);
	prompt(&data);
	printf("Liberamos el entorno\n");
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