
# ********** EJERCICIO 6 **********

#Script que muestra el contenido del fichero /etc/passwd (y parte del fichero /etc/group) de forma amigable. Recibirá una cadena de texto. Solo se mostrarán los usuarios que tengan esa cadena como shell de sistema (comprobar que la cadena está justo en ese campo y no en otro). Por cada usuario se imprimirá: 
	# 'logname' del usuario
	# 'UID' del usuario
	# 'groupname' de su grupo primario
	# 'GID' de su grupo primario
	# Información 'gecos'
	# Carpeta personal
	# 'Shell' por defecto
	# Un 1 si el usuario está actualmente logueado y un 0 en caso contrario.
	
#Autora: Irene Casares Rodríguez
	
	

#!/bin/bash
echo -e "\n"

# ----------------------------------
#      CONTROL DE ARGUMENTOS
# ----------------------------------

if [ $# -ne 1 ]
then
	echo "ERROR:Debe ser ./ejercicio6.sh <cadena> (por ejemplo, /bin/bash)"
	echo -e "\n"
	exit 1
fi


# ----------------------------------
#          PROCESAMIENTO
# ----------------------------------

lineaGrupo=$[4] #La primera línea en la que aparece el campo grupo. Se irá incrementando de 9 en 9
lineaLog=$[9] #La primera línea que indica si el usuario está logeado. Se irá incrementando de 9 en 9



grep -E "$1$" /etc/passwd | sed -r -e "s/^(.*):.*:(.*):(.*):(.*):(.*):(.*)$/==========\n->Logname:\1\n->UID:\2\n->Grupo:\n->GID:\3\n->gecos:\4\n->Home:\5\n->Shell por defecto:\6\n->Logueado:/" > fichero.txt
# grep -E "$1$" /ect/passwd  -->  escoge las líneas que terminen igual que la cadena pasada, de esta forma escogemos los usuarios cuya shell de sistema coincida con la cadena pues la shell se indica al final de la línea.
# sed -r -e ...  -->  reorganiza la información de las líneas (usuarios) pasadas por 'grep' de una forma más "amigable"


grupoID=$(grep -E "$1$" /etc/passwd | sed -r -e 's/^.*:.*:.*:(.*):.*:.*:.*$/\1/')
usuario=$(grep -E "$1$" /etc/passwd | sed -r -e 's/^(.*):.*:.*:.*:.*:.*:.*$/\1/') #Para comprobar si está logueado



for x in $grupoID
do
	nombreGrupo=$(sed -n -r -e "s/^(.*):.*:$x:.*$/\1/p" /etc/group)
	sed -i -r -e ""$lineaGrupo"s/^(.*)$/\1$nombreGrupo/" fichero.txt
	
	lineaGrupo=$[$lineaGrupo+9]
done



for x in $usuario
do
	if [ "$(who | grep "^$x.*$")" ]
	then
		sed -i -r -e ""$lineaLog"s/^(.*)$/\11/" fichero.txt
	else
		sed -i -r -e ""$lineaLog"s/^(.*)$/\10/" fichero.txt
	fi
	
	lineaLog=$[$lineaLog+9]
done



cat fichero.txt
rm fichero.txt



echo -e "\n"


