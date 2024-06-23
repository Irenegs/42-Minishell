## Parte 1a:
Chequear si el texto introducido está bien y extraer la información

## Parte 1b:
Gestión de hijos, pipes, ejecución de comandos

## Parte 2:
Gestión de señales - variable global
-> se pueden utilizarlas variables globales de readline.


## Parte 3:
Builtins
Conlleva la gestión de las variabes de entorno, inicialmente se obtienen con getenv, pero se pueden modificar o crear con export y eliminar con unset


# Por hacer:
## 1a
Heredoc vacío -> error 139


Gestionar $? -> se puede guardar en parse_and_execute como valor de retorno de execute/execute_only_child

heredoc + leaks: El delimitador se lee literalmente, no se transforma el delimitador. 'Delimitador' no expande las variables. 

heredoc + señales:
C-c dentro de heredoc lo corta y vuelve a la shell sin ejecutar ninguna instrucción $?=130
C-\ no hace nada
C-d cierra el heredoc con un error (bash: warning: here-document at line 160 delimited by end-of-file (wanted 'DELIMITADOR')) pero sigue con las instrucciones $?=0.

escribir errores
separar ejecución de built-ins
probar con varias pipes
probar pipes sin comando, solo con redirecciones
revisar si no necesitamos extern environ al tener la función getenv
revisar super_split porque la gestión de las \, que ya no es necesaria
proteger fallos de malloc y free de NULL -> extract element + norminette

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
