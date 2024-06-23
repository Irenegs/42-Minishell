
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
    int     *fd;
    char    *subs;
    int     childpid;
	int		status;
    char    **command;
    int     output;
    int     input;
    char    *heredoc;
    char    filename[20];
    int     i;

    p = 0;
    fd = malloc((pipes - 1) * 2 * sizeof(int));
    while (p <= pipes)
    {
        if (p != pipes)
            pipe(fd + 2 * p);
        childpid = fork();
        if (childpid == -1)
        {
            free(fd);
            return ;
        }
        if (childpid == 0)
        {
            i = 0;
            while (i < p - 1)
            {
                close(fd[2 * i + 1]);
                i++;
            }
            if (p == pipes)
            {
                close(fd[3]);
                close(fd[1]);
            }
            if (p != pipes)
            {
                dup2(fd[2 * p + 1], STDOUT_FILENO);
                close(fd[2 * p]);
            }
            if (p > 0)
            {
                if (access(".tmpfile", F_OK) != -1)
                    unlink(".tmpfile");
            }
            subs = extract_pipe(s, p);
            if (!subs)
            {
                free(fd);
                return ;
            }
            input = extract_input(subs);
            if (input > 0)
                dup2(input, STDIN_FILENO);
            else if (input == -1)
            {
                close(fd[2 * p - 2]);
                heredoc = get_heredoc(subs);
                input = open(".tmpfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
                write(input, heredoc, ft_strlen(heredoc));
                close(input);
                input = open(".tmpfile", O_RDONLY);
                dup2(input, STDIN_FILENO);
                free(heredoc);
            }
            else
            {
                dup2(fd[2 * (p - 1)], STDIN_FILENO);
                close(fd[2 * p - 1]);
            }
            output = extract_output(subs);
            if (output > 0)
                dup2(output, STDOUT_FILENO);
            command = extract_command(subs);
            if (!command)
            {
                free(fd);
                return ;
            }
            run_command(command);
            exit(1);
        }

        p++;
    }
    i = 0;
    while (i < pipes)
    {
        close(fd[2 * i + 1]);
        i++;
    }
    if (access(".tmpfile", F_OK) != -1)
        unlink(".tmpfile");
    while (wait(&status) > 0)
    {
	    printf("Exit: %d\n", status);
    }
    free(fd);
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
