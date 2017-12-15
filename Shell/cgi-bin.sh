#!/bin/sh

# Chopage des parametres, que ça soit GET ou POST
if [ $REQUEST_METHOD = "GET" ]
then
  CHAINE=$QUERY_STRING
else
  read CHAINE
fi

cat << EOF
Content-type: text/html

<html>
  <head>
    <title> Welcome </title>
  </head>
  <body>
    <h1> Welcome ! </h1>
EOF


#Construction de la vue en fonction de ce qui est trouvé dans les parametres
  #On récupère un tableau de parametres (a=b d=e ...)
LISTE=${CHAINE//&/ }
for param in $LISTE
do
  #Recuperation du champ et de la valeur
  champ=${param%=*}
  valeur=${param#*=}
  valeur=${$valeur//+/ }

  #Construction du html pour afficher les infos
  echo "<p> champ = $champ</p>"
  echo "<p> valeur = $valeur</p>"
done

cat << EOF
  </body>
</html>
EOF
