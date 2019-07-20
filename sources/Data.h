#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;



class Data {


  /*Les attributs sont une liste de photos verticales, une liste de photos horizontales
  et la liste de toutes les photos. Aussi le nombre de photos. */
    private :    // Attribut
      int                            nbPhotos;
      vector<vector<string>>         listeH;
      vector<vector<string>>         listeV;
      vector<vector<string>>         listeD;



    public :    // Methodes
      /* Constructeur */
      Data();

      /* Méthode qui sert à la lecture des données et à leur mise sous forme de 3 listes
      une pour toutes les images, une pour celles horizontales et une pour les verticales.
      Entrée : Le nom du fichier à lire et le pourcentage.
      Action : Extraire les données.
      Retourne : void.
      */
      void lectureFichier(string const, double);

      /* Getteur pour l'acquisition des données du fichier dans d'autres méthodes.
      Action : récupérer certaines données.
      Retourne :vecteur en deux dimensions de caractères.
      */
      vector<vector<string>> getListeH();
      vector<vector<string>> getListeV();
      vector<vector<string>> getListeD();

      /* Méthode qui créer le fichier avec la présentation construite par une des
      méthodes proposées dans les fichiers correspondants
      Entrée : Le nom du fichier où l'on va écrire et la présentaiton que l'on souhaite
      écrire.
      Action : Ecriture.
      Retourne : void.
      */
      void createFilePresentation(string const, vector<vector<string>> );

      /* Méthode qui sert à l'affichage
      Entrée : /
      Action : Afficher.
      Retourne : void.
      */
      void affichage();

    private :    // Methode
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


#endif //DATA_H
