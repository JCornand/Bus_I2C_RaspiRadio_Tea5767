# Bus_I2C_RaspiRadio_Tea5767

## Introduction
De nos jours nous pouvons avoir internet à n’importe quel endroit de la planète grâce à
nos téléphones mobiles… mais il fut un temps ou internet n’existait pas et un temps où on ne
pouvait l’avoir uniquement à la maison, il est aussi possible de se trouver dans une zone ou le
réseau n’est pas suffisant pour écouter la radio par internet…
L’objet de notre mini projet est de concevoir un petit système informatique qui sera
capable de recevoir et d’écouter la radio FM. Ce petit système sera greffé au système
Raspidomo existant que vous avez déjà utilisé.

Il existe des composants électroniques qui permettent de recevoir la radio, et qui peuvent
être pilotés par le bus i²C ! Il existe plusieurs références plus ou moins performantes et
onéreuses mais nous nous pencherons sur le composant TEA5767.

## Cahier des charges

Dans un premier temps, en guise de test unitaire, il faudra concevoir un programme de
test en ligne de commande. La fréquence à écouter sera passée en paramètre au programme
et le programme devra modifier la fréquence en pilotant le composant TEA5767.
Objectif suivant, une fois ce programme fonctionnel, création d'une
interface graphique composé d’une case pour saisir la fréquence à écouter et
un bouton pour valider la saisie et piloter le composant TEA5767.

## Objectifs du Projet

• Modifier la fréquence de réception de la Radio FM.
• Mettre en œuvre le bus I2C sur RaspberryPi.
• Mettre en œuvre le protocole I2C.
• S’approprier un schéma électronique.
• Utiliser une librairie de fonctions.
• Concevoir une application en langage C/C++.
• Ecrire une application en langage C/C++.
