# Google Hash Code 2019 "Photo slideshow"

## Auteure
Etudiante :

* Lachiheb Sarah

Sorbonne Université (UPMC) 2019 

## Préambule du Google Hash Code

Le 􏰀Google Hash Code􏰁 est une compétition de programmation pour des équipes d'étudiants ou de non-étudiants. La compétition est basée sur un problème, le plus souvent en optimisation combinatoire, et sur des instances de taille importante à résoudre. Le gagnant de cette compétition est celui qui a le meilleur 􏰀score􏰁, c'est-à-dire une solution optimisant la fonction objectif sur ces instances.

## Principe du projet

On considère dans ce projet la résolution d'un problème de choix d'ordre de passage de photos dans une présentation vidéo 􏰀a photo slideshow􏰁 en anglais. Pour cela, nous allons utiliser des techniques de résolution heuristique et exacte.

### Rapport :
|Fichier|
|:------|
|[Rapport](https://gitlab.com/ProjetLachiheb/google_hash_code_2019_photo_slidehow/blob/master/rapport_LACHIHEB.pdf)|

## Code source

### Exécution du code :

L’exécution du code se fait via la commande à faire sur le terminal. En effet, après avoir effectué la com- mande make il faut exécuter l’exécutable avec 3 arguments suivant, en premier le numéro de la méthode souhaitée (0 pour le sens de lecture, 1 pour le glouton, 2 pour la méta-heuristique, 3 pour le PLNE et 4 pour l’heuristique d’arrondi). Cela retourne, si nous faisons une erreur :

Veuillez saisir : **./exec \<Numéro de méthode souhaitée\> \<nom ficher(.txt)\>  \<pourcentage\>**

 Les numéros de méthodes associés sont :

* 0 : méthode sens de lecture du fichier. 
* 1 : méthode gloutonne.
* 2 : méthode métha-heuristique.
* 3 : méthode exacte PLNE
* 4 : méthode méthode heuristique d’arrondi PL

### Fichiers :

|Type de méthode | Type de méthode |
|:------| :---------------|
|Méthode gloutonnes| [click here](https://gitlab.com/ProjetLachiheb/google_hash_code_2019_photo_slidehow/blob/master/sources/PresentationSimple.cpp)|
|Méta-heuristiques | [click here](https://gitlab.com/ProjetLachiheb/google_hash_code_2019_photo_slidehow/blob/master/sources/PresentationSimple.cpp)|
|Formulations PLNE 1 | [click here](https://gitlab.com/ProjetLachiheb/google_hash_code_2019_photo_slidehow/blob/master/sources/PresentationExacte.cpp)|
|Formulations PLNE 2 | [click here](https://gitlab.com/ProjetLachiheb/google_hash_code_2019_photo_slidehow/blob/master/sources/PresentationExacte.cpp)|
|Heuristiques d'arrondi| [click here](https://gitlab.com/ProjetLachiheb/google_hash_code_2019_photo_slidehow/blob/master/sources/PresentationExacte.cpp)|
