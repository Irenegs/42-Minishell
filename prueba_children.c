
# include "minishell.h"

/*
static int	run_command(char **command)
{
    char *cmd;

	if (!command)
		return (-1);
	cmd = command_exists(command[0]);
	if (!cmd)
		return (127);
	execve(cmd, command, NULL);
	ft_out(command);
	return (-1);
}
void execute_child(char *s)
{
	char **command;

	command = extract_command(s);
	if (run_command(command) != 0)
            ft_out(command);
}
*/
void    execute(char *s, int pipes)
{
    int     p;
    int     fd[2];
    int     aux;
    char    *subs;
    int     childpid;
	int		status;
	char 	*arg[4];

	arg[0] = "/usr/bin/cat";
	arg[1] = "file";
	arg[2] = NULL;
    p = 0;// tal vez queramos separar el primer y último comando - pensar
    while (p < pipes)
    {
		printf("p %d\n", p);
        pipe(fd);//cerrar abrir fds de pipe
        subs = extract_pipe(s, p);
        if (!subs)
            return ;
        childpid = fork();
        if (childpid == 0)
        {
			printf("p-child %d\n", p);
			if (p == 0)
			{
				printf("Subs: %sAAAA\n", subs);
				dup2(fd[1], STDOUT_FILENO);
				execve("/usr/bin/cat", arg, NULL);
			}
			close(fd[0]);
			/*
            aux = extract_input(subs);
            if (aux != -1)
                dup2(fd[1], STDOUT_FILENO);*/
            //s se debe reemplazar por el substring de s referente al pipe; se debe calcular antes del fork
            /*
            printf("hijo\n");*/
        }
		/*
        aux = extract_output(subs);
        free(subs);*/
        dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
        p++;
    }
    //last command <- a lo mejor esto vale para onlychild
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
    /*else if (pipes == 0)
        execute_only_child(s);*/
    else if (pipes > 0)
        execute(s, pipes);
    
}

/*
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
*/