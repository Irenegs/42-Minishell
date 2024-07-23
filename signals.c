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

//iinterrupt the command and display a new prompt on a new line
void	ft_interrupt(int signal)
{
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit (SIGQUIT)\n", STDERR_FILENO);
	if (signal == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
}


// Maneja la señal de interrupción (SIGINT) para mostrar un nuevo prompt
void	ft_new_prompt(int signal)
{
	ft_putchar_fd('\n', STDOUT_FILENO); // Escribe una nueva línea en la salida estándar
	rl_replace_line("", 0); // Reemplaza la línea actual en la entrada
	rl_on_new_line(); // Mueve el cursor a una nueva línea
	rl_redisplay(); // Redibuja el prompt
	if (signal == SIGINT)
		global_signal = signal;

}

// Configura las señales en modo interactivo (esperando comandos del usuario)
void	ft_signals_start(void)
{
	signal(SIGINT, ft_new_prompt); // Asigna ft_new_prompt a SIGINT
	signal(SIGQUIT, SIG_IGN); // Ignora SIGQUIT
}

// Configura las señales cuando un comando está en ejecución
void	ft_signals_running(void)
{
	signal(SIGINT, ft_interrupt); // Asigna ft_interrupt a SIGINT
	signal(SIGQUIT, ft_interrupt); // Asigna ft_interrupt a SIGQUIT
}


void	ft_heredoc_handler(int signal)
{
   if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		
	}
}

void	ft_signals_new(void)

{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &ft_heredoc_handler;
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void ft_sig_def(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);

}




