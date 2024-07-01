/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:56:24 by irene             #+#    #+#             */
/*   Updated: 2024/07/01 18:33:16 by irene            ###   ########.fr       */
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

# define MAX_argv 100

extern int	global_signal;

typedef struct s_mix
{
	char	**m_env;
	char	**m_argv;
	char 	*input;
	int 	m_argc;
	int 	exit_status;
}				t_mix;

//error.c


//signals.c
void	ft_interrupt(int signal);
void	ft_new_prompt(int signal);
void	ft_heredoc_handler(int signal);
void	ft_signals_interactive(void);
void 	ft_signals_running(void);



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
int		is_builtin(char *cmd);


//built_in2.c
void ft_echo(char **command);
void ft_cd(char **command);
void ft_pwd(void);
void ft_export(t_mix *data, char **command);
void ft_unset(t_mix *data, char** command);

//built_in3.c
int ft_strcmp(const char *s1, const char *s2);
void ft_env(t_mix *data);
void ft_exit(char **command);
void execute_builtin(t_mix *data, char **command);
int ft_isnum(char *str);

//built_in4.c
char *create_env_entry(const char *key, const char *value);
char **new_entry(char **env, const char *key, const char *value, int size);
char **update_entry(char **env, int i, const char *key, const char *value);
void free_argv(char **argv);

//command.c
int	run_command(char **command, t_mix *data);

//execute.c
int    execute(t_mix *data, int pipes);
void    parse_and_execute(t_mix *data);

//execute_simple.c
int	execute_only_child(t_mix *data, char **heredocs);

//extract_command.c

char **extract_command(char *s);

//extract_elements.c
char *obtain_variable(char *s, int i);
char *extract_element(char *s, int pos);

//extract_file.c
int	extract_input(char *s, char	**heredocs, int p);
int extract_output(char *s);

//extract_pipe.c
char    *extract_pipe(char *s, int pipe);

//extract_utils.c
int	is_space(char c);
size_t	len_literal_word(char *s, int pos);
size_t	len_delimiter(char *s, int pos);
size_t len_quotes(char *s, int pos);
int	something_to_add(char *s, int pos);

//gnl.c
ssize_t	read_line(char **rem, int fd);
void	prepare_line(char *array[], char *rem);
char	*get_next_line(int fd);

//parser.c
int parser(char *s);

//pipe_utils.c
void	manage_multiple_pipes(int p, int pipes, int *fd);
void	close_pipes(int pipes, int *fd);
int		pipe_abortion(int *fd);

//heredocs.c
void	clean_and_free_heredocs(char **heredocs, int pipes);
int	get_heredocs(char **heredocs, t_mix *data, int pipes);

//heredoc_text.c
int	write_hd_file(char *s, char *filename);

//heredoc_expand.c
int	must_expand(char *delimiter, char *text);
char	*expand_string(char *s);

//heredoc_utils.c
int	number_of_heredocs(char *subs);
int	locate_n_hd(char *subs, int n);

//split_utils.c
int	is_escaped(char const *s, int i);
int	new_word(char const *s, char *sep, int i, int quotes);
int	ft_wc(char const *s, char *sep);
int	end_word(char const *s, char *sep, int i, int quot);

//super_split.c
char	**ft_out(char **arr);
char	**ft_super_split(char const *s, char *sep);


#endif
