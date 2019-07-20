#ifndef PRESENTATIONSIMPLE_H
#define PRESENTATIONSIMPLE_H

#include "Data.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;



class PresentationSimple {

    private :    // Attribut

  vector<vector<string>>      presentation;


    public :    // Methodes

        /* Constructeur */
      PresentationSimple();

      /* Méthode qui sert à la formation d'une présentation par sens de lecture
      Entrée : Les données "Data" du fichier
      Action : Dans le sens de lecture, affiche toutes les images de type "H"
      puis toutes celles de type "V".
      Retourne : void
      */
      void donnePresentationSimple(Data);

      /* Méthode qui sert à la formation d'une présentation par un algorithme
      glouton avec plusieurs amélioration qui permettent d'aller plus rapidement.
      Entrée : Les données "Data" du fichier
      Action : Prend au hasar une image et lui fait succéder la meilleur des "H"
      ou "V". Si c'est une "H" on recommence, si c'est une "V", on cherche le
      meilleur binome.
      Retourne : void
      */

      void presentationGlouton(Data);

      /* Méthode qui sert à la formation d'une présentation par une métha-heuristique
      basée un algorithme génétique.
      Entrée : Les données "Data" du fichier .
      Action : On lance m fils de la meilleur présentaiton par mutation. La mutation
      est d'échanger deux vignettes ou échanger deux images "V" de deux vignettes
      différentes. On fait cela sur p générations
      Retourne : void
      */
      void presentationMetha(Data);


      /* Méthode qui sert à la formation d'une présentation par une métha-heuristique
      basée un algorithme de voisinage.
      Entrée : Les données "Data" du fichier .
      Action : On lance un voisinage 2opt (ou 3opt) sur le meilleur trouvé et ainsi
      de suite jusqu'à ce que l'on ne s'améliore plus. Non utilisée car trop lente.
      Retourne : void
      */
      vector<vector<string>> troisOptimisation(vector<vector<string>>, int, Data, int);

      /* Retourne la présentation formée par les différentes méthodes.*/
      vector<vector<string>>  getPresentation();

      /* Méthode qui sert afficher une présentation
      Entrée : /
      Action : afficher
      Retourne : void
      */
      void afficher();
    private :    // Methode


      /* Méthode utilisée pour une tentative d'amélioration du glouton en formant les
      binome verticaux via leur ressemblances ou dissemblances.
      */
      bool haveCommun(vector<string>, vector<string>);



};


#endif
