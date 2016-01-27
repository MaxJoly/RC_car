# RC_car
Projet M2 ISEN

Il faut veiller à noter les paquets et les instructions nécessaires au fonctionnement du programme

Pour le GPS :
- installation des paquets :								sudo apt-get install gpsd gpsd-clients python-gps libgps-dev
- démarrage du node GPS :									rosrun gpsd_client gpsd_client _host:=localhost _port:=2947
- données publiées dans les topics /fix et /extended_fix
- (optionnel) affichage direct des données issues du GPS :	sudo gpscat -s 4800 /dev/tty[monUSB]
- (optionnel) passage du GPS en NMEA : 						gpsctl -n /dev/tty[monUSB]
- (optionnel) modification du port GPS : 					gpsd -S [port_des] /dev/tty[monUSB]

Pour l'initialisation des moteurs :
- (optionnel) vérification des paramètres : rosparam get /[monParametre]
- modification d'un paramètre : rosparam set /[monParametre]