/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irene <irgonzal@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:09:28 by irgonzal          #+#    #+#             */
/*   Updated: 2024/05/13 16:45:27 by irene            ###   ########.fr       */
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

void    execute(int pipes, char *s)
{
    pid_t   *childpid;
    int     *fd[2];

    printf("Pipes %d\n", pipes);
    childpid = malloc((pipes + 1) * sizeof(pid_t));
    if (forking(pipes, childpid) == -1)
    {
        free(childpid);
        return ;
    }
    run_child(childpid, fd, s, pipes);
    //printf("hola %d\n", childpid[0]);
    if (waitpid(-1, &childpid[0], 0) != -1)// && waitpid(-1, &childpid[1], 0) != -1 && waitpid(-1, &childpid[2], 0) != -1)
        printf("waitpid %d\n", childpid[0]);
    free(childpid);
    return ;
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

void    parse_and_execute(char *s)
{
    int pipes;

    if (!s || ft_strlen(s) == 0)
        return ;
    pipes = parser(s);
    printf("pipes %d\n",pipes);
    if (pipes == 0)
        execute_only_child(s);
    /*
    else if (pipes > 0)
        execute(pipes, s);*/
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
2) fork: childpid para cada proceso #pipes + 1
3) comprobar que ningún childpid es -1 => "exit" (volver al prompt) + error
4) en cada childpid != 0 y childpidothers == 0: establecer input y output y ejecutar el comando
5) Cerrar salidas/entradas de fds de pipes
6) waitpid, WEXITSTATUS para escribir errores
*/