/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:56:24 by irene             #+#    #+#             */
/*   Updated: 2024/06/11 17:47:19 by irgonzal         ###   ########.fr       */
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

extern char	**environ;

typedef struct s_mix
{
	char	**m_env;
	char	**m_path;
	char	**m_argv;
	int interrupted;

}				t_mix;

//signals.c
void	ft_sigint(int signum);
void	ft_sigquit(int signum);
void	signal_handler(void);
void ft_sleep(t_mix *data); // para hacer pruebas con las signals


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
char **new_entry(char **env, const char *key, const char *value, int size);
char **update_entry(char **env, int i, const char *key, const char *value);
void free_argv(char **argv);

//command.c
int	is_local(char *s);
static int	select_variable(char **environ);
static char	*get_path(char *s, int i, char **path);
static char	**get_path_variable(char **environ);
static char	*get_route(char *s, char **path);
char	*command_exists(char *s);

//execute.c
static int	run_command(char **command);
int execute_only_child(char *s);
void    execute(char *s, int pipes);
void    parse_and_execute(char *s);

//extract_command.c
static int len_cmd(char *s, int pos);
static int skip_word(char *s, int pos);
static int locate_cmd_position(char *s);
static int	find_next_word(char *s, int pos);
static char **split_command(char *s);
char **extract_command(char *s);

//extract_elements.c
char *obtain_variable(char *s, int i);
static char	*expand_double_quotes(char *s, int pos);
char *extract_element(char *s, int pos);

//extract_file.c
static int	locate_char_position(char *s, char c);
int extract_input(char *s);
int extract_output(char *s, int p);

//extract_pipe.c
static int locate_pipe_init(char *s, int pipe);
static int pipe_len(char *s, int pipe, int pos);
char    *extract_pipe(char *s, int pipe);

//extract_utils.c
int	is_space(char c);
size_t	len_literal_word(char *s, int pos);
size_t len_quotes(char *s, int pos);
int	something_to_add(char *s, int pos);

//gnl.c
static size_t	find_br(char *s);
ssize_t	read_line(char **rem, int fd);
void	prepare_line(char *array[], char *rem);
char	*get_next_line(int fd);

//parser.c
void change_insert(int *var, int pipe, int input, int output);
int redirection(char *s, int i, int insert[3]);
int	open_quotes(char *s);
int parser(char *s);

//prueba_children.c

void    execute(char *s, int pipes);
void    parse_and_execute(char *s);

//prueba_heredoc.c
static char *get_rawtext(char *delimiter);
static char *obtain_delimiter(char *del_str);
static char	*expand_string(char *s);
static int	must_expand(char *s);
char	*get_heredoc(char *s);

//split_utils.c
static int	is_separator(char c, char *sep);
int	is_escaped(char const *s, int i);
int	new_word(char const *s, char *sep, int i, int quotes);
int	ft_wc(char const *s, char *sep);
int	end_word(char const *s, char *sep, int i, int quot);

//super_split.c
char	**ft_out(char **arr);
static int	ch_to_print(char const *s, int i);
static int	len_next_word(char const *s, char *sep, int pos);
static int	copy_return_nonprint(char *dst, char const *s, int len);
char	**ft_super_split(char const *s, char *sep);


#endif
