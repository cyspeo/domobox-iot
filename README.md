# domobox-iot
Code ESP8266 pour gérer un programmateur de pompe de psicine.
Le micro proc est client et interroge le serveur (domobox-server) toute les minutes pour récupèrer la programmation.
Le programmation est un tableau de 24 boolean représentation l'activation de la pompe par heure.
A chaque requette, on récupère l'heure utilisé pour le calcul de l'état du relais.
Si la requette echoue, l'heure interne est incrémenté d'une minute et on utilise la programmation précédamment récupèré.

