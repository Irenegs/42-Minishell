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

void	ft_interrupt(int signal)
{
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit (SIGQUIT)\n", STDERR_FILENO);
	if (signal == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	ft_signals_running(void)
{
	signal(SIGINT, ft_interrupt);
	signal(SIGQUIT, ft_interrupt);
}

void	ft_sig_def(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);

}

static void	start_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	ft_signals_start(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &start_handler;
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
