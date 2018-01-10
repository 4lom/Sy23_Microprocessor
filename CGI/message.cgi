#!/bin/sh

TTY=/dev/ttyB0
#TTY=/dev/stdout

# Made by Zeissloff Louis


# en simulation le message envoyé sera accessible avec
# cat /dev/ttyB0

cat << EOFHEADER
Content-type: text/html

<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Message</title>
</head>
<body>
<h1 align=center >Affichage message</h1>
<hr align=center>
EOFHEADER

urldecode() {
    # urldecode <string>

    local url_encoded="${1//+/ }"
    printf '%b' "${url_encoded//%/\\x}"
}

if [ ${REQUEST_METHOD} = "GET" ]
 then
  if [ ${#QUERY_STRING} -gt 0 ]
   then
       messageaffichage=${QUERY_STRING}
    else
      messageaffichage="Technologies Mobiles et Systèmes Embarqués"  
   fi
   
   #Extract the message part (between message=  and &effet=).
   message_part=$(echo $messageaffichage | sed -re 's/&effet=.*//' | sed -re 's/message=//')
    #a=%49
    #printf '%b' "${${a//+/ }//%/\x}"
    #message_part=$(echo $message_part | sed -re 's/+//')
    #message_part=${message_part//+/ }
    message_part="$(echo $message_part | sed -e 's/%/\\x/g')"
    #message_part=$(printf "%b" "é")
    echo "<p>Message envoyé : $(printf "%b" "/Ox49")</p>"
    echo "<p>Message envoyé : $(printf "%s" "0O49")</p>"
    echo "<p>Message envoyé : $(printf "%b" "/ox49")</p>"
    echo "<p>Message envoyé : $(printf "%b" "0x49")</p>"
    #message_part=$(printf "%b" "$message_part") #"${message_part//%/\\x}")"
	#message_part=$("urldecode $message_part")
   
   #Extract the effect part (after effet=).
   effect_part=$(echo $messageaffichage | sed -re 's/^.*&effet=//')
   
   #Send the message with the effect on the bandeau.
   #echo -e "[00\V01\X$effect_part<$(echo $message_part | iconv -f UTF8 -t CP850 )>]" > "$TTY"
   echo -e "[00\V01\X$effect_part<$(echo $message_part)>]" > "$TTY"
   
   echo "<p>Message complet envoyé : ${messageaffichage}</p>"
   echo "<p>Message envoyé : ${message_part}</p>"
   echo "<p>Effet envoyé : ${effect_part}</p>"
 else
   echo "<p>Erreur methode : POST</p>"
fi 

echo "</body>"
echo "</html>"
