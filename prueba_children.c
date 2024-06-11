
# include "minishell.h"


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
    char    *heredoc;

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
            if (p != pipes)
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
            }
            subs = extract_pipe(s, p);
            if (!subs)
                return ;
            input = extract_input(subs);
            if (input > 0)
                dup2(input, STDIN_FILENO);
            else if (input == -1)
            {
                printf("1\n");
                heredoc = get_heredoc(subs);
                write(STDIN_FILENO, heredoc, ft_strlen(heredoc));
                free(heredoc);
            }
            output = extract_output(subs);
            if (output > 0)
                dup2(output, STDOUT_FILENO);
            command = extract_command(subs);
            if (!command)
                return ;
            run_command(command);
            exit(1);
        }
        dup2(fd[0], STDIN_FILENO);
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
    /*else if (pipes == 0)
        execute_only_child(s);*/
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
