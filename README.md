Por hacer:
- varias redirecciones en el mismo pipe: "< file1 < file 2"; "> file1 > file2"
OBS: cuando hay un | < file, prevalece el archivo e ignora la pipe 
- probar error de open output si el archivo ya existe y no tiene permisos de escritura
- probar con only_child
- probar con varias pipes
- en la función piping/execute child revisar si hay varios input/output
- probar pipes sin comando, solo con redirecciones
- heredoc
- revisar si no necesitamos extern environ al tener la función getenv -> ¿guardamos una copia para luego tener el unset?
- revisar super_split por la gestión de las \ que ya no es necesario


Cuidado con:
- errores de malloc
- 