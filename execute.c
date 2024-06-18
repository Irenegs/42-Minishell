/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:09:28 by irgonzal          #+#    #+#             */
/*   Updated: 2024/06/18 17:40:20 by irgonzal         ###   ########.fr       */
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
    char *heredoc;

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
        if (input == -1)
        {
            input = open("tmpfile", O_RDWR | O_TRUNC | O_CREAT, 0644);
            heredoc = get_heredoc(s);
            write(input, heredoc, ft_strlen(heredoc));
            dup2(input, STDIN_FILENO);
            //borrar tmpfile en algún momento
        }
        command = extract_command(s);
        printf("Comando: %s\n", command[0]);
        printf("Args: %s\n", command[1]);
        output = extract_output(s);
        if (output > 0)
            dup2(output, STDOUT_FILENO);
        if (run_command(command) != 0)
            ft_out(command);
        return (-1);
    }
    write(2, "hola!\n", 6);
    if (waitpid(-1, &childpid, 0) != -1)
        printf("exit!\n");
    return (0);
}

void    execute(char *s, int pipes)
{
    int     p;
    int     fd[2];
    int     aux;
    char    *subs;
    int     childpid;
    char **command;


    p = 0;// tal vez queramos separar el primer y último comando - pensar
    while (p <= pipes)
    {
        //pipe(fd);cerrar abrir fds de pipe
        subs = extract_pipe(s, p);
        if (!subs)
            return ;
        printf("Subs: %sAAAA\n", subs);
        childpid = fork();
        if (childpid == 0)
        {
            aux = extract_input(subs);
            //if (aux != -1)
            //    dup2(fd[1], STDOUT_FILENO);
            command = extract_command(subs);
            printf("command: %s-%s\n", command[0], command[1]);
            ft_out(command);
            //s se debe reemplazar por el substring de s referente al pipe; se debe calcular antes del fork
            //execute_child(subs);
        }
        aux = extract_output(subs);
        //if (aux != -1)
        //dup2(fd[0], STDIN_FILENO);
        free(subs);
        p++;
    }
    //last command <- a lo mejor esto vale para onlychild
    /*
    while (wait(&status) > 0)
    {
	    printf("Exit: %d\n", WEXITSTATUS(&status));
    }*/
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

/*void show_leaks(void)
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