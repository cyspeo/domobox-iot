# domobox-iot
Code ESP8266 pour gérer un programmateur de pompe de psicine.
Le micro processeur est client et interroge le serveur (domobox-server) toutes les minutes pour récupèrer la programmation.
Le programmation est un tableau de 24 booleans représentant l'activation de la pompe par heure.
A chaque requette, on récupère l'heure utilisée pour le calcul de l'état du relais.
Si la requette échoue, l'heure interne est incrémentée d'une minute et on utilise la programmation précédamment récupèrée.

