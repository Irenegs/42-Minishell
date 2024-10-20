/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:56:24 by irene             #+#    #+#             */
/*   Updated: 2024/10/20 12:10:12 by pablgarc         ###   ########.fr       */
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

//error.c
void	*write_error_null(int error_code);
int		perror_int(int return_value);
int		write_error_int(int error_code, int return_value);

//signals.c
void	ft_interrupt(int signal);
void	ft_signals_start(void);
void	ft_signals_running(void);
void	ft_sig_def(void);

//signals_hd.c
void	ft_signals_hd(void);

//struct.c
void	*ft_free_env(char **env);
void	ft_init_mix(t_mix *data, char **envp);

//built_in_check.c
int		is_builtin(char *cmd);
int		is_special_builtin(char *cmd);
int		execute_builtin(t_mix *data, char **command);

//built_in.c
int		ft_echo(char **command);
int		ft_cd(char **command, t_mix *data);
int		ft_pwd(t_mix *data);
int		ft_export(t_mix *data, char **command);
int		ft_unset(t_mix *data, char **command);

//built_in_env_exit.c
int		ft_env(t_mix *data);
int		ft_exit(char **command, t_mix *data);

//built_in_utils1.c
char	*create_env_entry(const char *key, const char *value);
char	**new_entry(char **env, const char *key, const char *value, int size);
char	**update_entry(char **env, int i, const char *key, const char *value);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isnum(char *str);

//built_in_utils2.c
int		find_env_index(char **env, const char *key);
char	**au_env(char **env, const char *key, const char *value);
char	**copy_env_without_entry(char **env, int index, int size);
char	**remove_env(char **env, const char *key);
int		valid_varname(char *str);

//built_in_utils3.c
void	empty_export(t_mix *data);
int		process_export_command(t_mix *data, char *cmd);

//command.c
int		run_command(char **command, t_mix *data);

//command_utils.c
int		is_local(char *s);
char	**get_path_variable(t_mix *data);

//execute.c
int		execute(t_mix *data);
void	parse_and_execute(t_mix *data);

//execute_simple.c
int		execute_zero_pipes(t_mix *data);
int		status_treatment(int *status);

//extract_command.c
char	**extract_command(char *s, t_mix *data);

//extract_elements.c
char	*obtain_variable(char *s, int i, t_mix *data);
//char	*extract_element(char *s, int *pos, t_mix *data);
char    **extract_element(char *s, int pos, t_mix *data);
int		something_to_add(char *s, int pos);

//extract_file.c
int		extract_input(char *s, t_mix *data, int p);
int		locate_char_position(char *s, char c);
int		locate_char_position_quotes(char *s, char c);
int		extract_output(char *s, t_mix *data);

//extract_pipe.c
char	*extract_pipe(char *s, int pipe);

//extract_utils.c
size_t	len_literal_word(char *s, int pos);
size_t	len_quotes(char *s, int pos);
int		len_cmd_str(char *str);

//extract_utils2.c
char	*extract_cmd_str(char *str);
void	manage_quotes(int *quotes, char c);
int		len_skip_word(char *str, int pos);
void	copy_cmd(char *orig, char *res);
int		locate_char_position(char *s, char c);

//parser.c
int		parser(char *s);

//pipe_utils.c
void	manage_multiple_pipes(int p, int pipes, int *fd);
void	close_pipes(int pipes, int *fd);
int		pipe_abortion(int *fd);

//general_utils.c
int		is_quote(char c);
int		is_space(char c);
int		is_separator(char c);
char	**join_arrays(char ***array);
char	*increment_shlvl(char *env_var);

//heredoc_files.c
void	clean_and_free_heredocs(char **heredocs, int pipes);
int		get_heredocs(t_mix *data);

//heredoc_delimiter.c
char	*obtain_delimiter(char *del_str);

//heredoc_text.c
int		write_hd_file(char *s, int number_of_hd, t_mix *data);

//heredoc_expand.c
int		must_expand(char *delimiter, char *text);
char	*expand_heredoc(char *input_str, t_mix *data);
char	*expand_variable(char *orig, char *input_str, int pos, t_mix *data);

//heredoc_utils.c
int		number_of_heredocs(char *subs);
int		locate_n_hd(char *subs, int n);

//split_utils.c
int		is_escaped(char const *s, int i);
int		new_word(char const *s, char *sep, int i, int quotes);
int		ft_wc(char const *s, char *sep);
int		end_word(char const *s, char *sep, int i, int quot);

//super_split.c
char	**ft_out(char **arr);
char	**ft_super_split(char const *s, char *sep);

//variable_utils.c
int		select_variable(char *var_name, t_mix *data);
char	*ft_getenv(char *var_name, t_mix *data);
char	*obtain_variable(char *s, int i, t_mix *data);
size_t	len_variable(char *str, int pos);
size_t	len_varname(char *str, int *pos);

//expander_quotes.c
char	**unquote(char **element);
char	*expand_str(char *str, t_mix *data);
int		variables_to_expand(char *str);
void	add_char(char **result, char *orig, int pos);

//split_element.c
char	**split_element(char *str);
#endif