/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:56:24 by irene             #+#    #+#             */
/*   Updated: 2024/05/07 19:18:31 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/ioctl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft/libft.h"

# define INPUT 0
# define DELIMITER 1
# define COMMAND 2
# define ARG 3
# define OUTPUT 4
# define KOUTPUT 5

typedef struct s_word
{
	char			*content;
	int				function;
	struct s_word	*next;
	
}	t_word;

t_word	*parser(char *s);
t_word	*ft_lstnew(char *content, int func);
void	ft_lstadd_front(t_word **lst, t_word *new);
int		ft_lstsize(t_word *lst);
t_word	*ft_lstlast(t_word *lst);
void	ft_lstadd_back(t_word **lst, t_word *new);
void	ft_lstdelone(t_word *lst, void (*del)(void *));
void	ft_lstclear(t_word **lst, void (*del)(void *));
void	ft_lstiter(t_word *lst, void (*f)(void *));
t_word	*ft_lstmap(t_word *lst, void *(*f)(void *), void (*del)(void *));
int is_metacharacter(char c);
#endif