/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:36:46 by irgonzal          #+#    #+#             */
/*   Updated: 2024/05/19 19:19:49 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	locate_char_position(char *s, char c)
{
	int i;

	i = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int extract_input(char *s)
{
	int		fd;
	int		pos;
	char	*filename;
	int		aux_fd;

	if (!s)
		return (-1);
	pos = locate_char_position(s, '<');
	if (pos == -1)
		return (-2);
	if (pos == -2)
		return (1);//heredoc
	filename = extract_element(s, pos);
	if (!filename)
		return (-2);//-1 para gestionar el error?
	fd = open(filename, O_RDONLY);
	free(filename);
	//perror("minishell");//función de escritura de errores?
	aux_fd = extract_input(s + pos + 1);
	if (aux_fd > -2)
		fd = aux_fd;
	return (fd);
}

int extract_output(char *s)
{
	int		fd;
	int		pos;
	char	*filename;
	int		aux_fd;

	if (!s)
		return (-1);
	pos = locate_char_position(s, '>');
	if (pos == -1)
		return (-2);
	if (s[pos + 1] == '>')
		pos++;
	filename = extract_element(s, pos);
	if (!filename)
		return (-2);//-1 para gestionar el error?
	if (pos == locate_char_position(s, '>'))
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT, 0644);
	free(filename);
	//perror("minishell");//función de escritura de errores?
	aux_fd = extract_output(s + pos + 1);
	if (aux_fd > -2)
		fd = aux_fd;
	return (fd);
}
