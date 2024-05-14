Por hacer:
- función extract_command -> pasar a super_split la subcadena y luego liberarla
- implementar la gestión de comillas sin cerrar -> que no de segfault, etc.
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