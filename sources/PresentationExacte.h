#ifndef PRESENTATIONEXACTE_H
#define PRESENTATIONEXACTE_H

#include "Data.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;



class PresentationExacte {

  /*Les attributs sont une matrice des couts de chaque transitions et une présentation. */
    private :    // Attribut

      vector<vector<int>>         couts;
      vector<vector<string>>      presentation;


    public :    // Methode
    /* Constructeur */
      PresentationExacte();


      /* Méthode qui, par exécution d'un PLNE par flots permet l'exécution d'un eméthode
      exacte dans le but de répondre à l'objectif d'une présentation optimale(que pour les H)
      Entrée : Les données extraites du fichier
      Action : Avoir un ordre optimal.
      Retourne : void.
      */
      void plne(Data);

      /* Méthode qui, par exécution d'un PL par flots permet l'exécution d'un eméthode
      par arrondi dans le but de répondre à l'objectif d'une présentation heuristique
      (que pour les H)
      Entrée : Les données extraites du fichier
      Action : Avoir un ordre heuristique par arrondi.
      Retourne : void.
      */
      void plne_arrondi(Data donnees);

      /* Méthode qui sert à la comparaison d'élément de type pair
      Entrées : Les deux pairs à comparer.
      Action : Comparaison pour extraire le plus grand, true si oui et false sinon.
      Retourne : un booléen .
      */
      bool operator() (double, double);


      /* Getter utilisé pour récupéré la présentation formée par un des deux programmes linéaire.
      Entrée : /
      Action : Récupération de données.
      Retourne : la présentation sous forme d'un vecteur 2D de caractères.
      */
      vector<vector<string>>  getPresentation();

    private : 
      /* Méthode qui sert au calcul d'une matrice coût servant aux programmes linéaire.
      Entrée : Les données Data du fichier.
      Action : Calculer un matrice des couts des transitions.
      Retourne : void.
      */
      void MatriceCout(Data);



};

#endif
