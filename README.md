Por hacer:
- locate_cmd_position hay que cambiarlo y hay que hacer un len_cmd para sacar substr y pasarlo a supersplit
- varias redirecciones en el mismo pipe: "< file1 < file 2"; "> file1 > file2" -> recursión en extract input/output => revisar cuando hay espacios entre < y el nombre del archivo
OBS: cuando hay un | < file, prevalece el archivo e ignora la pipe 
- probar error de open output si el archivo ya existe y no tiene permisos de escritura
- probar con only_child
- probar con varias pipes
- probar pipes sin comando, solo con redirecciones
- heredoc
- revisar si no necesitamos extern environ al tener la función getenv -> ¿guardamos una copia para luego tener el unset?
- revisar super_split porque la gestión de las \ que ya no es necesaria


Cuidado con:
- errores de malloc
- 