/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:31:28 by pablgarc          #+#    #+#             */
/*   Updated: 2024/07/23 17:02:55 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	perror_int(int return_value)
{
	perror(NULL);
	return (return_value);
}

int	write_error_int(int error_code, int return_value)
{
	if (error_code == 1)
		write(2, "Malloc error\n", 13);
	if (error_code == 2)
		write(2, "Write heredoc error\n", 20);
	return (return_value);
}

void	*write_error_null(int error_code)
{
	if (error_code == 1)
		write(2, "Malloc error\n", 13);
	return (NULL);
}
