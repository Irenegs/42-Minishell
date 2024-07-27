# Por hacer:
## Probar siempre
- Probar (ya funciona, pero probar cada vez que se toquen redirecciones): < /dev/urandom cat | head -1; cat | cat | ls
Valgrind leaks:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./minishell
valgrind --track-fds=yes --trace-children=yes; --child-silent-after-fork=yes

- parser permitir cosas raras entrecomilladas
- generar entorno por defecto => leer https://unix.stackexchange.com/questions/280453/understand-the-meaning-of para la gestión inicial de $_ pasamos de todo y hardcodeamos
escribir errores => perror(NULL) y cambiar printf;
proteger fallos de malloc y free de NULL


## Signals:
Ctrl - \ debe no hacer nada

### heredoc + señales:
C-c dentro de heredoc lo corta y vuelve a la shell sin ejecutar ninguna instrucción $?=130
C-\ no hace nada
C-d cierra el heredoc con un error (bash: warning: here-document at line 160 delimited by end-of-file (wanted 'DELIMITADOR')) pero sigue con las instrucciones $?=0.

## Parser:
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


## Builtins:
echo with option -n
pwd with no options
env with no options or arguments
cd with only a relative or absolute path -> cuando exit está en una pipe no tiene efecto. Tiene que ejecutarse desde execute_zero_pipes.
export with no options -> cuando exit está en una pipe no tiene efecto. Tiene que ejecutarse desde execute_zero_pipes.
unset with no options -> cuando exit está en una pipe no tiene efecto. Tiene que ejecutarse desde execute_zero_pipes.
exit with no options -> cuando exit está en una pipe no tiene efecto. Tiene que ejecutarse desde execute_zero_pipes y matar el proceso padre (o ser llamado desde ese proceso).


# Listado de archivos:
command.c -> buscar el archivo y devuelve la ruta
execute.c -> coge la línea introducida en minishell, la parsea (mira la estructura) y la ejecuta
extract_command.c -> de una cadena entre pipes, extrae el comando y los argumentos del mismo
extract_element.c -> de una cadena extrae la primera palabra sustituyendo las variables, gestionando las comillas, etc.
extract_file.c -> de una cadena entre pipes, extrae el archivo input (<) y el output (>)
extract_pipe.c -> de una cadena larga, extrae el contenido entre pipes de la n-ésima pipe
extract_utils.c -> funciones sueltas comunes a todos los archivos extract_*.c
main.c
parser.c -> chequea si la cadena introducida en minishell está bien escrita o no
split_utils.c -> funciones sueltas para super_split.c
super_split.c -> split que admite varios separadores a un tiempo


# FUNCIONES PERMITIDAS

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
The wait() system call suspends execution of the calling thread until one of its children terminates. 
The  call wait(&wstatus) is equivalent to: waitpid(-1, &wstatus, 0); 
The  waitpid()  system  call suspends execution of the calling thread until a child specified by pid argument has changed state.  
By default, waitpid() waits only for terminated children
In other words, wait3() waits of any child, while wait4() can be used to select a specific child, or children, on which to wait.



## Señales:
https://www.codequoi.com/en/sending-and-intercepting-a-signal-in-c/
https://www.gnu.org/software/libc/manual/html_node/Signal-Handling.html Hasta Blocking Signals incluido
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler); returns  the  previous value of the signal handler, or SIG_ERR on error
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact); => 0/-1  -> to change the action taken by a process on receipt of a specific signal. 
int sigemptyset(sigset_t *set);=> 0/-1 -> initializes the signal set given by set to empty, with all signals excluded from the set.
int sigaddset(sigset_t *set, int signum) => 0/-1; -> add signal signum from set.

## Termios
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


## Shell grammar
https://www.ibm.com/docs/en/zos/3.1.0?topic=shell-grammar
https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html#
https://en.wikipedia.org/wiki/LL_parser
