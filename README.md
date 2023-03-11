## Driver pour un capteur à ultrasons interfacé avec un système Linux

### Description de la solution

1. Connexion à la carte via *ssh*

2. Se placer dans le répertoire */dossierTest*

3. *make*

4. Lancer le driver avec *sudo insmod main.ko*

5. Mettre la pin 17 à l'état haut pour émettre un signal sur la pin trigger

6. Regarder les logs du kernel pour contrôler la distance mesurée avec *dmesg*

7. Arrêter le driver avec *sudo rmmod main.ko*


### Auteurs

Paul RENAUlT, Alexandre BOURDOIS, Geoffroy PIGEON, Paul MOREAU.