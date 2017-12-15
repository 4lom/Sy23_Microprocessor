#!/bin/sh

#Affiche un simple formulaire faisant des requetes POST au device gèrant le bandeau
cat << EOF
Content-type= text/html

<html>
  <head>
    <title> Hello ! </title>
    <meta http-equiv="content-type" content="text/html; charset=UTF-8">
  </head>
  <body>
    <h1> Hello You ! :D </h1>
    <form action="@IP ici :D/pageCGI" method="POST">
      <label for="message"> Ton message : </label>
      <input type="text" name="message" />
      <input type="submit" />
    </form>
  </body>
</html
