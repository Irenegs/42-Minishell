/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:09:28 by irgonzal          #+#    #+#             */
/*   Updated: 2024/05/16 22:20:47 by irene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int calculate_child_number(pid_t *childpid, int pipes)
{
    int i;
    int uniq;
    int number;

    i = 0;
    uniq = 0;
    number = -1;
    while(i < pipes)
    {
        if (childpid[i] != 0 && uniq == 0)
        {
            uniq = 1;
            number = i;
        }
        else if (childpid[i] != 0 && uniq == 1)
            return (-1);
    }
    return (number);
}

void run_child(pid_t *childpid, int **fd, char *s, int pipes)
{
    int n;

    printf("Run\n");
    n = calculate_child_number(childpid, pipes);
    if (n != -1)
        printf("Number %d\n", n);
}

int forking(int pipes, pid_t *childpid)
{
    int n;

    n = 0;
    childpid[n] = fork();
    while (childpid[n] != -1 && n < pipes)
    {
        n++;
        childpid[n] = fork();
    }
    if (n < pipes)
        return (-1);
    return (0);
}
*/
/*

}*/
/*
static int	run_command(char **command)
{
	if (!command)
		return (-1);
	cmd = command_exists(command[0]);
	if (!cmd)
		return (127);
	execve(cmd, command, environ);
	ft_out(command);
	return (-1);
}*/

int execute_only_child(char *s)
{
    int input;
    int output;
    char **command;

    input = extract_input(s);
    printf("Input fd: %d\n", input);
    close(input);
    //dup2(input, STDIN_FILENO);
    output = extract_output(s);
    printf("Output fd: %d\n", output);
    close(output);
    /*
    dup2(output, STDOUT_FILENO);
    command = extract_command(s);
    if (run_command(s) != 0)
        ft_out(command);
    return (-1);*/
    return (0);
}

int locate_pipe_init(char *s, int pipe)
{
    int i;
    int p;

    i = 0;
    p = 0;
    while(p < pipe)
    {
        if (s[i] == '|')
            p++;
        i++;
    }
    while (s[i] == '|' || is_space(s[i]) == 1)
    {
        i++;
    }
    return (i);
}

int pipe_len(char *s, int pipe, int pos)
{
    int len;

    len = 0;
    while (s[pos + len] != '|' && s[pos + len] != '\0')
        len++;
    while(is_space(s[pos + len]) == 1 || s[pos + len] == '|')
        len--;
    return (++len);
}

char    *extract_pipe(char *s, int pipe)
{
    int pos;
    int len;

    pos = 0;
    len = 0;
    pos = locate_pipe_init(s, pipe);
    len = pipe_len(s, pipe, pos);
    return (ft_substr(s, pos, len));
}

void    execute(char *s, int pipes)
{
    int     p;
    int     fd[2];
    int     aux;
    char    *subs;

    p = 0;// tal vez queramos separar el primer y último comando - pensar
    while (p < pipes)
    {
        //pipe(fd);cerrar abrir fds de pipe
        subs = extract_pipe(s, p);
        printf("Subs: %sAAAA\n", subs);
        //fork();
        aux = extract_input(subs);
        if (aux != -1)
            dup2(fd[1], STDOUT_FILENO);
        //s se debe reemplazar por el substring de s referente al pipe; se debe calcular antes del fork
        //execute_child(subs);
        aux = extract_output(subs);
        free(subs);
        dup2(fd[0], STDIN_FILENO);
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
    printf("pipes %d\n",pipes);
    if (pipes == 0)
        execute_only_child(s);
    else if (pipes > 0)
        execute(s, pipes);
}

int main(int argc, char **argv)
{
    char *s = argv[1];

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
4) en cada childpid != 0 y childpidothers == 0: establecer input y output y ejecutar el comando
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