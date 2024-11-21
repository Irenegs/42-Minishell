/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_hd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:31:25 by pablo             #+#    #+#             */
/*   Updated: 2024/11/21 23:24:52 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sigint_hd(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_exit_status = 130;
	}
	else if (signal == SIGQUIT)
	{
		write(1, "Quit: \n", 8);
		g_exit_status = 131;
	}
	close(STDIN_FILENO);
	/*	
	ft_putchar_fd('\n', STDOUT_FILENO);
	if (signal == SIGINT)
		g_exit_status = 130;
	close(STDIN_FILENO);*/
}

void	ft_signals_hd(void)
{
	signal(SIGINT, ft_sigint_hd);
	signal(SIGQUIT, ft_sigint_hd);
}
