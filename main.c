/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:58:01 by irene             #+#    #+#             */
/*   Updated: 2024/04/13 13:33:37 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void signal_handler(int signum)
{
	if (signum == SIGQUIT)
		printf("Hi, signal C-\\ %d\n", signum);//Poner algo aquí, sin nada escribe ^\ y sale
	else if (signum == SIGINT)//esto no funciona
		printf("You did C-c\n");
}

/*
void show_leaks(void)
{
	system("leaks minishell");
}
*/
int main(void)
{
	char *s;
	struct sigaction sa;

    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);

	//atexit(show_leaks);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		exit(3);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit(4);
	s = readline("Write:");
	while (s && *s)
	{
		printf("String:\n%s\n", s);
		add_history(s);
		printf("Length: %lu\n", ft_strlen(s));
		free(s);
		s = readline("Write:");
		if (*s == '\n')
			rl_on_new_line();
	}
	rl_clear_history();
}

/*

Makefile:
Hacer que pille la minishell

Prompt:
readline lee y devuelve la línea de stdin (malloc).
Si la línea no es vacía, se guarda en con add_history en un histórico que gestiona la propia función readline.
No parece que add_history deje leaks
Ctrl - C debe simplemente establecer una nueva línea de prompt => Escribe ^C y nueva línea de promp
Ctrl - D debe salir del programa => Lo hace por defecto
Ctrl - \ debe no hacer nada
Cuando dejamos la línea vacía (intro directamente) revisar qué hace



- Leer man de las funciones permitidas
- Establecer prompt que escuche la entrada estandar
- Parseo de la entrada estandar
- Establecimiento de built-ins
- Otros comandos
- Otras consideraciones del subjetc

stdio.h

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



https://www.gnu.org/software/libc/manual/html_node/Signal-Handling.html Hasta Blocking Signals incluido

typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler); returns  the  previous value of the signal handler, or SIG_ERR on error
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact); => 0/-1  -> to change the action taken by a process on receipt of a specific signal. 
int sigemptyset(sigset_t *set);=> 0/-1 -> initializes the signal set given by set to empty, with all signals excluded from the set.
int sigaddset(sigset_t *set, int signum) => 0/-1; -> add signal signum from set.



kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, 



opendir, readdir, closedir,
strerror, perror, 

int isatty(int fd); -> function tests whether fd is an open file descriptor referring to a terminal. returns 1 if fd is an open file descriptor referring to a terminal; otherwise 0 is returned
char *ttyname(int fd); -> The function ttyname() returns a pointer to the null-terminated pathname of the terminal device that is open on the file descriptor fd, or NULL on error.
int ttyslot(void); -> (?)


execve,
int ioctl(int fd, unsigned long request, ...); => 0/-1; 



getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs




Valgrind leaks:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./minishell
 * */
