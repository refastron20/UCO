#!/bin/bash

if [ $# -lt 1 ]; then
  echo "Debe introducir solo un argumento: shell del sistema"
  exit -1
fi

cat /etc/passwd | grep -Eo ".*:$1" > fich.tmp

cat fich.tmp | sed -r 's/^(.*):.*:(.*):(.*):(.*):(.*):(.*)/==========\'\n'Logname: \1\'\n'->UID: \2\'\n'->Grupo:\'\n'->GID: \3\'\n'->gecos: \4\'\n'->Home:\5\'\n'->Shell por defecto:\6\'\n'->Logeado:/' > fich2.tmp

cat fich2.tmp > fich.tmp

grupoID=$(grep -E "$1$" /etc/passwd | sed -r -e 's/^.*:.*:.*:(.*):.*:.*:.*$/\1/')
lineaGrupo=$[4]

for x in $grupoID
do
	nombreGrupo=$(sed -n -r -e "s/^(.*):.*:$x:.*$/\1/p" /etc/group)
	sed -i -r -e ""$lineaGrupo"s/^(.*)$/\1$nombreGrupo/" fich.tmp

	lineaGrupo=$[$lineaGrupo+9]
done

usuario=$(grep -E "$1$" /etc/passwd | sed -r -e 's/^(.*):.*:.*:.*:.*:.*:.*$/\1/')
lineaLog=$[9]
for x in $usuario
do
	if [ "$(who | grep "^$x.*$")" ]
	then
		sed -i -r -e ""$lineaLog"s/^(.*)$/\11/" fich.tmp
	else
		sed -i -r -e ""$lineaLog"s/^(.*)$/\10/" fich.tmp
	fi

	lineaLog=$[$lineaLog+9]
done

cat fich.tmp
rm fich.tmp fich2.tmp
