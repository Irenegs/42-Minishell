## Parte 1a:
Chequear si el texto introducido está bien y extraer la información

## Parte 1b:
Gestión de hijos, pipes, ejecución de comandos

## Parte 2:
Gestión de señales - variable global

## Parte 3:
Builtins






# Por hacer:
## 1a
Revisar comando dado por variable
$?
heredoc
proteger malloc
leaks
escribir errores
separar ejecución de built-ins
probar con varias pipes
probar pipes sin comando, solo con redirecciones
revisar si no necesitamos extern environ al tener la función getenv -> ¿guardamos una copia para luego tener el unset?
revisar super_split porque la gestión de las \ que ya no es necesaria


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