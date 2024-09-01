/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:28:17 by pablgarc          #+#    #+#             */
/*   Updated: 2024/09/01 17:59:17 by pablgarc         ###   ########.fr       */
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
	if (error_code == 3)
		write(2, "cd: too many arguments\n", 23);
	if (error_code == 4)
		write(2, "cd: HOME not set\n", 17);
	if (error_code == 5)
		write(2, "Not a valid identifier\n", 23);
	if (error_code == 6)
		write(2, "Command not found\n", 19);
	return (return_value);
}

void	*write_error_null(int error_code)
{
	if (error_code == 1)
		write(2, "Malloc error\n", 13);
	return (NULL);
}
