/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:58:01 by irene             #+#    #+#             */
/*   Updated: 2024/04/12 19:11:02 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void show_leaks(void)
{
	system("leaks minishell");
}
*/
int main(void)
{
	char *s;

	//atexit(show_leaks);
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
Ctrl - C debe simplemente establecer una nueva línea de prompt
Ctrl - D debe salir del programa
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

signal, sigaction, sigemptyset, sigaddset, 
kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, 

execve,

opendir, readdir, closedir,
strerror, perror, 
isatty, ttyname, ttyslot, ioctl,

getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs




Valgrind leaks:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./minishell
 * */
