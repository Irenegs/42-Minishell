/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:56:24 by irene             #+#    #+#             */
/*   Updated: 2024/05/25 13:58:09 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <errno.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern char	**environ;
int	is_space(char c);
int 	is_metacharacter(char c);
int 	parser(char *s);
void    parse_and_execute(char *s);
int		extract_input(char *s);
int		extract_output(char *s);
char 	**extract_command(char *s);
char	**ft_super_split(char const *s, char *sep);
int		is_escaped(char const *s, int i);
int		new_word(char const *s, char *sep, int i, int quotes);
int		ft_wc(char const *s, char *sep);
int		end_word(char const *s, char *sep, int i, int quot);
char **extract_command(char *s);
char	**ft_out(char **arr);
char	*command_exists(char *s);
char    *extract_pipe(char *s, int pipe);
size_t	len_literal_word(char *s, int pos);
size_t len_quotes(char *s, int pos);
int	something_to_add(char *s, int pos);
char *extract_element(char *s, int pos);
char *obtain_variable(char *s, int i);
char	*get_next_line(int fd);
#endif