#!/bin/bash
if [ -z $1 ] || [ ! -f $1 ]; then
echo "Debe introducir un fichero como argumento"
exit -1
fi

echo "$(sed -re '/^$/d; /^ .*$/d; /^=*$/d; s/([1-9]*hr [1-9]*min)/|-> Duración:\1/; s/(.*)(\()(.*\/.*\/.*)(\))(.*)/|-> Fecha de estreno: \3/;
s/Dirigida por (.*)/|-> Director: \1/; s/(Reparto: .*)/|-> \1/; s/(^[^(|)].*)/Título: \1/' $1)"
