#ifndef MYCHECKER_H
#define MYCHECKER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;



class MyChecker {


    /* Les attributs nécessaire sont le nombre de vignettes nécessaire à une
    présentation et le score par vignettes, c'est à dire le score pour chaque
    transitions*/
    private :    // Attributs
      int nbVignettes;
      vector<int> scoreParVignette;



    public :    // Methodes
    /* Constructeur */
      MyChecker();


      /* Méthode qui sert au calcul des résultats d'une présentation entière présente dans
      le fichier résultats.
      Entrée : Le nom du fichier à lire et la liste de toutes les données du fichier
      correspondant à la présentation afin d'extraire les mots clefs.
      Action : calculer le score total.
      Retourne : le score sous forme d'un int.
      */
      int scorePresentation(string const, vector<vector<string>> );

      /* Méthode qui sert au calcul d'une transitions entre deux images
      Entrée : Les deux listes de mots clefs des deux vignettes, ou images lors
      de la construction de la présentaiton.
      Action : calculer le score d'une transition.
      Retourne : le score sous forme d'un int.
      */
      int getScoreTransition(vector<string> , vector<string> );

      /* Méthode qui sert au calcul des résultats d'une présentation entière présente dans
      un vector de vector de chaine de caractères et non dans un fichier.
      Entrée : La présentation et la liste de toutes les données du fichier
      correspondant à la présentation afin d'extraire les mots clefs.
      Action : calculer le score total.
      Retourne : le score sous forme d'un int.
      */
      int scorePresentation(vector<vector<string>>, vector<vector<string>> );

      /* Méthode qui sert à la lecture des résultarts, résultats consignés dans
      un fichier.
      Entrée : Le nom du fichier à lire et le pourcentage.
      Action : Extraire les données.
      Retourne : void.
      */
      void lectureFichier(string const, vector<vector<string>>);

    private :    // Methodes
      /* Méthode qui sert avoir le minimim de trois éléments
      Entrée : trois int.
      Action : trouver le minimum.
      Retourne : le minimum sous forme d'un int.
      */
      int min(int, int, int);

      /* Méthode qui sert à la formation d'une sous chaîne
      Entrée : Une chaine de caractères, un délimitateur, une chaine résultat
      Action : Découpe une chaine de caractères.
      Retourne : void
      */
      void split(const string &chaine, char delimiteur, std::vector<std::string> &elements);

      /* Méthode qui sert à la formation d'une sous chaîne
      Entrée : Une chaine de caractères, un délimitateur
      Action : Découpe une chaine de caractères.
      Retourne : chaine de caractères
      */
      vector<string> split(const string &chaine, char delimiteur);



};


#endif
