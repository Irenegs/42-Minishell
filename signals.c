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

void	ft_sigint(int signum)
{
	if (signum == SIGINT)
	{
		//printf("SIGINT recibida\n");

		/*
		cuando el crtl+c interrumpe proceso imprime dos veces el prompt
		hace falta un flag de proceso en ejecuccion para poner aqui
		un if y un else y que lo imprima bien
		
		*/

        rl_replace_line("", 0); // borra la linea actual del prompt
        write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line(); //mueve cursor a nueva linea
        rl_redisplay();
		
	}
}
void	ft_sigquit(int signum)
{
	if (signum == SIGQUIT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_handler(void)
{
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
}

void ft_sleep(t_mix *data)
{
	int seconds;

    if (data->m_argv[1] == NULL)
    {
        printf("ft_sleep: expected argument\n");
        return;
    }

    seconds = ft_atoi(data->m_argv[1]);
    if (seconds < 0)
    {
        printf("ft_sleep: invalid time '%s'\n", data->m_argv[1]);
        return;
    }

    sleep(seconds);
}
