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
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	if (signal == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
}

// Signal handler for SIGINT (Ctrl-C)
// When the user presses Ctrl-C, the signal is sent to the process
// and the handler is called. The handler writes a newline character
// to the standard output, replaces the current line with an empty
// string, moves the cursor to the beginning of the line and redisplays
// the prompt.
void	ft_new_prompt(int signal)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	if (signal == SIGINT)
		global_signal = signal;
}

void	ft_heredoc_handler(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_replace_line("", 0);
	global_signal = signal;
}


void	ft_signals_interactive(void)
{
	signal(SIGINT, ft_new_prompt);
	signal(SIGQUIT, SIG_IGN);
}



void	ft_signals_running(void)
{
	signal(SIGINT, ft_interrupt);
	signal(SIGQUIT, ft_interrupt);
}


