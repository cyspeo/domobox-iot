# domobox-iot
Code ESP8266 pour gérer un programmateur de pompe de psicine.
Le micro processeur est client et interroge le serveur (domobox-server) toutes les minutes pour récupèrer la programmation.
Le programmation est un tableau de 24 booleans représentant l'activation de la pompe par heure.
A chaque requette, on récupère l'heure utilisée pour le calcul de l'état du relais.
Si la requette échoue, l'heure interne est incrémentée d'une minute et on utilise la programmation précédamment récupèrée.

La programmation de la puce se fait avec micropython.
Voir cet excelent blog ici : https://blog.bandinelli.net/index.php?post/2016/10/23/Micropython-sur-ESP8266%2C-l-%C3%A9lectronique-toujours-plus-libre-et-puissante-%21

Le chargement du firmware marche avec cette instruction : 
python -m esptool --port /dev/ttyUSB0 -b 115200 write_flash -fm dio --verify -ff 40m -fs 32m 0x0 /path/to/esp8266-20170823-v1.9.2.bin 


