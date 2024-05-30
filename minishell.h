/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:56:24 by irene             #+#    #+#             */
/*   Updated: 2024/05/30 22:47:21 by pablo            ###   ########.fr       */
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

#define MAX_argv 100 

typedef struct s_mix
{
	char	**m_env;
	char	**m_path;
	char	**m_argv;

}				t_mix;


//struct.c
void	ft_free_env(char **env);
void	ft_init_mix(t_mix *data);
char	**ft_copy_env(char **envp);
char  **ft_copy_argv(int argc, char **argv);
void	ft_fill_struct(t_mix *data, int argc, char **argv, char **envp);

//buil_in.c
int find_env_index(char **env, const char *key);
char **add_or_update_env(char **env, const char *key, const char *value);
char **copy_env_without_entry(char **env, int index, int size);
char **remove_env(char **env, const char *key);


//built_in2.c
void ft_echo(t_mix *data);
void ft_cd(t_mix *data);
void ft_pwd(void);
void ft_export(t_mix *data);
void ft_unset(t_mix *data);

//built_in3.c
int ft_strcmp(const char *s1, const char *s2);
void ft_env(t_mix *data);
void ft_exit(t_mix *data);
void execute_builtin(char **argv, t_mix *data);

//built_in4.c
char *create_env_entry(const char *key, const char *value);
char **copy_env_with_new_entry(char **env, const char *key, const char *value, int size);
char **update_existing_entry(char **env, int index, const char *key, const char *value);


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
char	*get_heredoc(char *s);
#endif