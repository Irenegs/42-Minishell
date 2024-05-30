/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:58:01 by irene             #+#    #+#             */
/*   Updated: 2024/05/30 22:23:48 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//para probar compilar:
//gcc -o beta built_in2.c built_in.c built_in3.c built_in4.c  struct.c main.c libft/libft.a -lreadline
void prompt(t_mix *data)
{
    char *input;
    char **argv;

    while (1)
    {
        input = readline("Minishell: ");
        if (*input)
            add_history(input);
        if(*input != '\0')
        {
            argv = ft_split(input, ' ');
            if (argv)
            {
                data->m_argv = argv;
                execute_builtin(argv, data);
                free(argv);
            }
            free(input);
        }
    }
}

int main(int argc, char **argv, char **envp)
{
    t_mix data;

    if (argc != 1 || !argv)
       return (1);

    ft_init_mix(&data);
    ft_fill_struct(&data, argc, argv, envp);
    prompt(&data);
    ft_free_env(data.m_env);
    ft_free_env(data.m_argv);
    return (0);
}


/*
void	prompt(void)
{
	char *s;

	s = readline("Minishell:");
	while (s)
	{
		//printf("String:\n%s\n", s);
		add_history(s);
		parse_and_execute(s);
		free(s);
		s = readline("Minishell:");
	}
	//rl_clear_history();
}


void signal_handler(int signum)
{
	if (signum == SIGQUIT)
		printf("Minishell:");//Esto no funciona bien
	else if (signum == SIGINT)
		printf("^CMinishell:");//No vuelve a la terminal
}

/*
void show_leaks(void)
{
	system("leaks minishell");
}

int main(void)
{
	struct sigaction sa;

	//atexit(show_leaks);
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
	//sigaddset(&sa.sa_mask, SA_RESTART);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		exit(3);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit(4);
	prompt();
	return (0);
}



Prompt:
readline lee y devuelve la línea de stdin (malloc).
Si la línea no es vacía, se guarda en con add_history en un histórico que gestiona la propia función readline.
No parece que add_history deje leaks.

Signals:
Ctrl - \ debe no hacer nada



Parser:
Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).
Implement redirections:
< should redirect input.
> should redirect output.
<< should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
>> should redirect output in append mode.
Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
Handle $? which should expand to the exit status of the most recently executed foreground pipeline.





Builtins:
echo with option -n
cd with only a relative or absolute path
pwd with no options
export with no options
unset with no options
env with no options or arguments
exit with no options


FUNCIONES PERMITIDAS

char *readline (const char *prompt) -> hay que liberar el resultado
void add_history(char *line) -> to save the line away in a history list of such lines.
void rl_clear_history (void) -> Clear the history list by deleting all of the entries,
int rl_on_new_line (void) -> Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline. 
void rl_replace_line (const char *text, int clear_undo) -> Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared. 
void rl_redisplay (void) -> Change what’s displayed on the screen to reflect the current contents of rl_line_buffer. 

printf, 
malloc, free, 
write, access, open, read,close, 

fork, dup, dup2, pipe, 

wait, waitpid, wait3, wait4, 
pid_t wait(int *wstatus);
pid_t wait3(int *wstatus, int options, struct rusage *rusage);
pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);
The wait() system call suspends execution of the calling thread until one of its children terminates. The  call wait(&wstatus) is equivalent to: waitpid(-1, &wstatus, 0); The  waitpid()  system  call suspends execution of the calling thread until a child specified by pid argument has changed state.  By default, waitpid() waits only for terminated children
In other words, wait3() waits of any child, while wait4() can be used to select a specific child, or children, on which to wait.



Señales:
https://www.codequoi.com/en/sending-and-intercepting-a-signal-in-c/
https://www.gnu.org/software/libc/manual/html_node/Signal-Handling.html Hasta Blocking Signals incluido
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler); returns  the  previous value of the signal handler, or SIG_ERR on error
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact); => 0/-1  -> to change the action taken by a process on receipt of a specific signal. 
int sigemptyset(sigset_t *set);=> 0/-1 -> initializes the signal set given by set to empty, with all signals excluded from the set.
int sigaddset(sigset_t *set, int signum) => 0/-1; -> add signal signum from set.
Termios
https://blog.nelhage.com/2009/12/a-brief-introduction-to-termios-termios3-and-stty/
int tcgetattr(int fildes, struct termios *termios_p); => 0/-1
int tcsetattr(int fildes, int optional_actions, const struct termios *termios_p); => 0/-1
int ioctl(int fd, unsigned long request, ...); => 0/-1; It takes a file descriptor, a numeric “request” code, and an unspecified number of other arguments. ioctl looks up whatever device (or file system, network protcol, or whatever) is backing that file descriptor, and hands it the “request” and the arguments to do with as they will.


kill, exit,

getcwd, chdir, opendir, readdir, closedir,

stat, lstat, fstat, unlink, 
stat()  retrieves information about the file pointed to by pathname; the differences for fstatat() are described below.
lstat() is identical to stat(), except that if pathname is a symbolic link, then it returns information about the link itself, not the file that the link refers to.
fstat()  is  identical to stat(), except that the file about which information is to be retrieved is specified by the file descriptor fd.
int unlink(const char *pathname); deletes a name from the filesystem.  If that name was the last link to a file and no processes have the file open, the file is deleted and the space it was using is made available for reuse.


strerror, perror, 

int isatty(int fd); -> function tests whether fd is an open file descriptor referring to a terminal. returns 1 if fd is an open file descriptor referring to a terminal; otherwise 0 is returned
char *ttyname(int fd); -> The function ttyname() returns a pointer to the null-terminated pathname of the terminal device that is open on the file descriptor fd, or NULL on error.
int ttyslot(void); -> (?)


execve,
int ioctl(int fd, unsigned long request, ...); => 0/-1; 
It takes a file descriptor, a numeric “request” code, and an unspecified number of other arguments. ioctl looks up whatever device (or file system, network protcol, or whatever) is backing that file descriptor, and hands it the “request” and the arguments to do with as they will.


getenv
char *     getenv(const char *name); obtains the current value of the environment variable, name.  The application should not modify the string pointed to by the getenv() function.





tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs => Seguramente se utilice para algunos built-ins
https://www.gnu.org/software/termutils/manual/termcap-1.3/html_chapter/termcap_2.html


Valgrind leaks:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./minishell


Observaciones:
<< EOF
C-c sale del heredoc



Shell grammar
https://www.ibm.com/docs/en/zos/3.1.0?topic=shell-grammar
https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html#
https://en.wikipedia.org/wiki/LL_parser
*/
