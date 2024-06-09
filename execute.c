/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:09:28 by irgonzal          #+#    #+#             */
/*   Updated: 2024/06/09 17:45:45 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_command(char **command)
{
    char *cmd;

	if (!command)
		return (-1);
	cmd = command_exists(command[0]);
	if (!cmd)
		return (127);
	execve(cmd, command, environ);
	ft_out(command);
	return (-1);
}

int execute_only_child(char *s)
{
    int input;
    int output;
    char **command;
    int childpid;

    childpid = fork();
    if (childpid == -1)
    {
        printf("Childerror\n");
        exit(1);
    }
    if (childpid == 0)
    {
        input = extract_input(s);
        if (input > 0)
            dup2(input, STDIN_FILENO);
        output = extract_output(s);
        if (output > 0)
            dup2(output, STDOUT_FILENO);
        command = extract_command(s);
        if (!command)
            return (-1);
        run_command(command);
        exit(1);
    }
    if (waitpid(-1, &childpid, 0) != -1)
        printf("exit!\n");
    return (0);
}

void    execute(char *s, int pipes)
{
    int     p;
    int     fd[2];
    char    *subs;
    int     childpid;
	int		status;
    char    **command;
    int     output;
    int     input;

    p = 0;
    while (p <= pipes)
    {
        if (p != pipes)
            pipe(fd);
        childpid = fork();
        if (childpid == -1)
            return ;
        if (childpid == 0)
        {
            subs = extract_pipe(s, p);
            if (!subs)
                return ;
            if (p != pipes)
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
            }
            input = extract_input(subs);
            if (input > 0)
            {
                dup2(input, STDIN_FILENO);
            }
            output = extract_output(subs);
            if (output > 0)
            {
                dup2(output, STDOUT_FILENO);
            }
            command = extract_command(subs);
            if (!command)
                return ;
            run_command(command);
            exit(1);
        }
        dup2(fd[0], STDIN_FILENO);
        close(STDIN_FILENO);
        close(fd[1]);
        p++;
    }
    while (wait(&status) > 0)
    {
	    printf("Exit: %d\n", status);
    }
}

void    parse_and_execute(char *s)
{
    int pipes;

    if (!s || ft_strlen(s) == 0)
        return ;
    pipes = parser(s);
    if (pipes == -1)
        printf("Parse error\n");
    else if (pipes == 0)
        execute_only_child(s);
    else if (pipes > 0)
        execute(s, pipes);
    
}

void show_leaks(void)
{
    system("leaks a.out");
}

int main(int argc, char **argv)
{
    char *s = argv[1];
    atexit(show_leaks);
    if (argc == 1)
        return (1);
    parse_and_execute(s);
    return (0);
}
/*

1) Establecer pipes


Bucle:
- establecer pipe (Quizás solo haga falta una pipe?)
- fork
> - redirigir con dup2(fd1, stdout)
> - ejecutar todos menos el último
- dup(fd0, stdin)


- al final e último hijo recoge el stdout (dup2()) para hacer el último comando
2) fork: childpid para cada proceso #pipes + 1
3) comprobar que ningún childpid es -1 => "exit" (volver al prompt) + error
5) Cerrar salidas/entradas de fds de pipes
6) waitpid, WEXITSTATUS para escribir errores
*/

/*

Gestión esperar a los hijos

while ((wpid = wait(&status)) > 0)
{
	exiting(WEXITSTATUS(&status), 1, argv);
}
//lo va a hacer en orden ?

*/