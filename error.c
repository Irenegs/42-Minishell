/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:28:17 by pablgarc          #+#    #+#             */
/*   Updated: 2024/08/28 18:12:24 by irgonzal         ###   ########.fr       */
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
		write(2, " not a valid identifier\n", 24);
	return (return_value);
}

void	*write_error_null(int error_code)
{
	if (error_code == 1)
		write(2, "Malloc error\n", 13);
	if (error_code == 2)
		write(2, "Bad substitution\n", 17);
	return (NULL);
}
