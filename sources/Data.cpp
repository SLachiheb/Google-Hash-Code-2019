#include "Data.h"
#include <cmath>
#include <fstream>
using namespace std;



/* Dans ce fichier sont présentes les méthodes servant à l'exploitation des
données :

Les méthodes et attributs présentes dans ce fichier sont ;

  private :    // Attributs
  int                            nbPhotos;
  vector<vector<string>>         listeH;
  vector<vector<string>>         listeV;
  vector<vector<string>>         listeD;



  public :    // Methodes
  Data();

  void lectureFichier(string const, double);
  void affichage();
  vector<vector<string>> getListeH();
  vector<vector<string>> getListeV();
  vector<vector<string>> getListeD();
  void createFilePresentation(string const, vector<vector<string>> );

  private :    // Methodes
  void split(const string &chaine, char delimiteur, std::vector<std::string> &elements);
  vector<string> split(const string &chaine, char delimiteur);

*/


/* Constructeur */
Data::Data() {
}




/* Méthode qui sert à la formation d'une sous chaîne
Entrée : Une chaine de caractères, un délimitateur, une chaine résultat
Action : Découpe une chaine de caractères.
Retourne : void
*/
void Data::split(const std::string &chaine, char delimiteur, std::vector<std::string> &elements)
{
    std::stringstream ss(chaine);
    std::string sousChaine;
    while (std::getline(ss, sousChaine, delimiteur))
    {
        elements.push_back(sousChaine);
    }
}


/* Méthode qui sert à la formation d'une sous chaîne
Entrée : Une chaine de caractères, un délimitateur
Action : Découpe une chaine de caractères.
Retourne : chaine de caractères
*/
vector<string> Data::split(const string &chaine, char delimiteur)
{
    std::vector<std::string> mots;
    split(chaine, delimiteur, mots);
    return mots;
}



/* Méthode qui sert à la lecture des données et à leur mise sous forme de 3 listes
une pour toutes les images, une pour celles horizontales et une pour les verticales.
Entrée : Le nom du fichier à lire et le pourcentage.
Action : Extraire les données.
Retourne : void.
*/
void Data::lectureFichier(string const nom_fichier, double pourcent){

    std::ifstream fichier;

    fichier.open(nom_fichier.c_str());

    if (fichier.is_open()) {
      string ligne;
  	  getline(fichier, ligne);
      vector<string> mots = split(ligne, ' ');
  	  this->nbPhotos = stoi(mots[0]);
  	  int indice(0);
      this->listeD = vector<vector<string>> ((int)((pourcent * this->nbPhotos)/100));
      for (int i(0); i < (int)((pourcent * this->nbPhotos)/100); i++) {
    	  getline(fichier, ligne);
        vector<string> mots = split(ligne, ' ');

        if (mots[0] == "H"){
    	    this->listeH.push_back(vector<string>(1));
    	    this->listeH[listeH.size()-1] = vector<string>(stoi(mots[1]) + 1);
          this->listeD[i] = vector<string>(stoi(mots[1]));
    	    this->listeH[this->listeH.size()-1][0] = to_string(indice);
    	    for(int j(1); j < (stoi(mots[1]) + 1); j++){
    	      this->listeH[this->listeH.size()-1][j] = mots[j+1];
            this->listeD[i][j-1] = mots[j+1];
          }
    	  }

    	  if (mots[0] == "V"){
    	    this->listeV.push_back(vector<string>(1));
    	    this->listeV[listeV.size()-1] = vector<string>(stoi(mots[1]) + 1);
          this->listeD[i] = vector<string>(stoi(mots[1]));
    	    this->listeV[this->listeV.size()-1][0] = to_string(indice);
    	    for(int j(1); j < (stoi(mots[1]) + 1); j++){
    	       this->listeV[this->listeV.size()-1][j] = mots[j+1];
             this->listeD[i][j-1] = mots[j+1];
           }
  	    }
  	     indice++;
      }
    }
    else {
        std::cout << "Erreur : Impossible d'ouvrir le fichier en lecture Euclid" << std::endl;
    }
}






/* Méthode qui sert à l'affichage
Entrée : /
Action : Afficher.
Retourne : void.
*/
void Data::affichage() {
  for(int i(0); i < this->listeH.size(); i++){
    for(int j(0); j < this->listeH[i].size(); j++){
      cout << this->listeH[i][j] << " ";
    }
    cout << endl;
  }
  for(int i(0); i < this->listeV.size(); i++){
    for(int j(0); j < this->listeV[i].size(); j++){
      cout << this->listeV[i][j] << " ";
    }
    cout << endl;
  }
}




/* Méthode qui créer le fichier avec la présentation construite par une des
méthodes proposées dans les fichiers correspondants
Entrée : Le nom du fichier où l'on va écrire et la présentaiton que l'on souhaite
écrire.
Action : Ecriture.
Retourne : void.
*/
void Data::createFilePresentation(string const nom_fichier, vector<vector<string>> presentation){
  ofstream fichier(nom_fichier, ios::out);

  if (fichier) {
    fichier << presentation.size() << endl;
    for(int i(0); i < presentation.size(); i++){
      for(int j(0); j < presentation[i].size(); j++){
        if (presentation[i][j] != "")
          fichier << presentation[i][j] << " ";
      }
      fichier << endl;
    }
  }
}



/* Getteur pour l'acquisition des données du fichier dans d'autres méthodes.
Action : récupérer certaines données.
Retourne :vecteur en deux dimensions de caractères.
*/
vector<vector<string>> Data::getListeH(){
  return this->listeH;
}

vector<vector<string>> Data::getListeV(){
  return this->listeV;
}

vector<vector<string>> Data::getListeD(){
  return this->listeD;
}
