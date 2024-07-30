/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_hd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:31:25 by pablo             #+#    #+#             */
/*   Updated: 2024/07/30 19:44:25 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sigint_hd(int signal)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	if (signal == SIGINT)
		g_exit_status = 130;
	close(STDIN_FILENO);
}

void	ft_signals_hd(void)
{
	signal(SIGINT, ft_sigint_hd);
	signal(SIGQUIT, SIG_IGN);

}
