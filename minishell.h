/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:56:24 by irene             #+#    #+#             */
/*   Updated: 2024/12/13 09:36:46 by pablgarc         ###   ########.fr       */
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
# include <asm-generic/signal-defs.h>
# include <x86_64-linux-gnu/bits/sigaction.h>

# define MAX_ARGV 100

extern int	g_exit_status;

typedef struct s_mix
{
	char	**m_env;
	char	*input;
	int		exit_status;
	char	**heredocs;
	int		*pipesfd;
	int		pipes;
}				t_mix;

//built_in_cd_pwd.c 
int		ft_cd(char **command, t_mix *data);
int		ft_pwd(t_mix *data);

//built_in_check.c
int		is_builtin(char *cmd);
int		execute_builtin(t_mix *data, char **command);
int		choose_and_execute_builtin(t_mix *data, char **command);

//built_in_ehco.c
int		ft_echo(char **command);

//built_in_env.c
int		ft_env(t_mix *data);

//built_in_exit.c
int		ft_exit(char **command, t_mix *data);

//built_in_export.c 
int		ft_export(t_mix *data, char **command);

//built_in_unset.c 
int		ft_unset(t_mix *data, char **command);

//built_in_utils1.c
char	*create_env_entry(const char *key, const char *value);
char	**new_entry(char **env, const char *key, const char *value, int size);
char	**update_entry(char **env, int i, const char *key, const char *value);
int		ft_isnum(char *str);
int		ft_strcmp(const char *s1, const char *s2);

//built_in_utils2.c
int		find_env_index(char **env, const char *key);
char	**au_env(char **env, const char *key, const char *value);
int		valid_varname(char *str);

//execute_redirections.c
int		manage_redirections(int p, t_mix *data, char *subs);

//error.c
int		perror_int(int return_value);
int		write_error_int(int error_code, int return_value);
void	*write_error_null(int error_code);

//command.c
int		run_command(char **command, t_mix *data);

//command_utils.c
int		is_local(char *s);
char	**get_path_variable(t_mix *data);

//execute_simple.c
int		status_treatment(int *status);
int		execute_zero_pipes(t_mix *data);

//execute.c
int		extract_pipe_and_execute(int p, t_mix *data);
int		execute_several_pipes(t_mix *data);
int		execute_pipes(t_mix *data);
int		execute(t_mix *data);
void	parse_and_execute(t_mix *data);

//expander_quotes.c
char	**unquote(char **element);
void	add_escaped_quote(char **result, char *orig, int pos);
char	*escape_quotes_in_variable(char *str);

//expander_string.c
char	*expand_string(char *str, t_mix *data);

void	add_char(char **result, char *orig, int pos);

char	*ft_getenv(char *var_name, t_mix *data);
char	*obtain_variable(char *s, int i, t_mix *data);
char	*expand_variable(char *orig, char *input_str, int pos, t_mix *data);

int		variables_to_expand(char *str);

char	**extract_command(char *s, t_mix *data);

char	**escape_quotes_in_array(char **array);
char	**extract_element(char *s, int pos, t_mix *data);

int		extract_input(char *s, t_mix *data, int p);

int		ft_open(char *filename, int mode);
char	*extract_filename(char *s, int *pos, t_mix *data);
int		extract_output(char *s, t_mix *data);

char	*extract_pipe(char *s, int pipe);

char	**split_command(char *s, t_mix *data);

size_t	len_literal_word(char *s, int pos);
size_t	len_quotes(char *s, int pos);
int		len_cmd_str(char *str);
int		len_skip_word(char *str, int pos);

int		locate_cmd_position(char *s);
int		locate_char_position(char *s, char c);
int		locate_char_position_quotes(char *s, char c);

char	*obtain_delimiter(char *del_str);

char	*expand_heredoc(char *input, t_mix *data);
int		must_expand(char *delimiter, char *text);

int		number_of_heredocs(char *subs);
int		locate_n_hd(char *subs, int n);

int		get_heredocs(t_mix *data);
void	clean_and_free_heredocs(char **heredocs, int pipes);

int		write_hd_file(char *s, int hd_number, t_mix *data);

int		parser_errors(char *s);

int		parser_manage_quotes(char *s, int pos);
int		count_pipes(char *s);
int		white_string(char *s);
int		parser(char *s);

void	manage_multiple_pipes(int p, int pipes, int *fd);
void	close_pipes(int pipes, int *fd);
int		pipe_abortion(int *fd);

void	ft_signals_hd(void);

void	ft_signals_running(void);
void	ft_signals_start(void);

char	**split_element(char *str);

char	**join_arrays(char ***array);

int		is_escaped(char const *s, int i);
int		new_word(char const *s, char *sep, int i, int quotes);
int		ft_wc(char const *s, char *sep);
int		end_word(char const *s, char *sep, int i, int q);

void	ft_init_mix(t_mix *data, char **envp);

char	**ft_super_split(char const *s, char *sep);

int		count_env_variables(char **envp);

int		is_quote(char c);
int		is_space(char c);
int		is_separator(char c);
void	manage_quotes(int *quotes, char c);

void	free_array(char ***arr);
char	**ft_out_exception(char **arr, int n);
char	**ft_out(char **arr);
char	**free_partial_array(char **array, int filled);

int		select_variable(char *var_name, t_mix *data);
size_t	len_varvalue(char *str, int pos);
size_t	len_varname(char *str, int *pos);

#endif