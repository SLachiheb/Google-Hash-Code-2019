#include "MyChecker.h"
#include "Data.h"
#include <cmath>
#include <fstream>
#include <algorithm>
using namespace std;


/* Dans ce fichier sont présentes les méthodes dites servants aux calcule des
scores de présentation et de transition.

Les méthodes et attributs présents dans ce fichier sont ;
    private :    // Attributs
      int nbVignettes;
      vector<int> scoreParVignette;
    public :    // Methodes
      MyChecker();
      void lectureFichier(string const, vector<vector<string>>);
      int scorePresentation(string const, vector<vector<string>> );
      int getScoreTransition(vector<string> , vector<string> );
      int scorePresentation(vector<vector<string>>, vector<vector<string>> );

    private :    // Methodes
      int min(int, int, int);
      void split(const string &chaine, char delimiteur, std::vector<std::string> &elements);
      vector<string> split(const string &chaine, char delimiteur);

*/

/* Constructeur */
MyChecker::MyChecker() {
}


/* Méthode qui sert au calcul des résultats d'une présentation entière présente dans
le fichier résultats.
Entrée : Le nom du fichier à lire et la liste de toutes les données du fichier
correspondant à la présentation afin d'extraire les mots clefs.
Action : calculer le score total.
Retourne : le score sous forme d'un int.
*/
int MyChecker::scorePresentation(string const nom_fichier, vector<vector<string>> listeD){
  lectureFichier(nom_fichier, listeD);
  int score(0);
  for(int i(0); i < this->scoreParVignette.size(); i++)
    score += this->scoreParVignette[i];
  return score;
}



/* Méthode qui sert au calcul d'une transitions entre deux images
Entrée : Les deux listes de mots clefs des deux vignettes, ou images lors
de la construction de la présentaiton.
Action : calculer le score d'une transition.
Retourne : le score sous forme d'un int.
*/
int MyChecker::getScoreTransition(vector<string> liste1, vector<string> liste2){
  vector<int> resultat(3, 0);


  for(int i(0); i < liste1.size(); i++){
    for(int j(0); j < liste2.size(); j++){
      if(liste1[i] == liste2[j])
        resultat[0]++;
    }
  }
  resultat[1] = liste1.size() - resultat[0];
  resultat[2] = liste2.size() - resultat[0];
  sort(resultat.begin(), resultat.end(), greater<>());
  return  resultat[2];
}




/* Méthode qui sert au calcul des résultats d'une présentation entière présente dans
un vector de vector de chaine de caractères et non dans un fichier.
Entrée : La présentation et la liste de toutes les données du fichier
correspondant à la présentation afin d'extraire les mots clefs.
Action : calculer le score total.
Retourne : le score sous forme d'un int.
*/
int MyChecker::scorePresentation(vector<vector<string>> presentation, vector<vector<string>> listeD){

    int indice1(0);
    int indice2(0);
    vector<string> liste1;
    vector<string> liste2;
    bool test(true);
    string ligne;
    int scoreTransition;
    vector<string> mots1;
    vector<string> mots2;
    int sizeM1(0);
    int sizeM2(0);



	    this->nbVignettes = presentation.size();
      this->scoreParVignette = vector<int>(presentation.size() - 1, 0);

      mots1 = presentation[0];
      if (mots1[1] == "")
        sizeM1 = 1;
      else
        sizeM1 = 2;

      for (int i(0); i < (this->nbVignettes -1); i++) {
        liste1.clear();
        liste2.clear();
        mots2 = presentation[i+1];
        if (mots2[1] == "")
          sizeM2 = 1;
        else
          sizeM2 = 2;

        if (sizeM1 == 1){
          indice1 = stoi(mots1[0]);
          for(int i(0); i < listeD[indice1].size(); i++)
            liste1.push_back(listeD[indice1][i]);
	      }

	      else if (sizeM1 == 2){
          indice1 = stoi(mots1[0]);
          indice2 = stoi(mots1[1]);
          for(int i(0); i < listeD[indice1].size(); i++)
            liste1.push_back(listeD[indice1][i]);
          for(int i(0); i < listeD[indice2].size(); i++){
            test = true;
            for(int j(0); j < liste1.size(); j++){
              if (liste1[j] == listeD[indice2][i]){
                test = false;
                break;
              }
            }
            if(test)
              liste1.push_back(listeD[indice2][i]);
          }
	      }


        if (sizeM2 == 1){
          indice1 = stoi(mots2[0]);
          for(int i(0); i < listeD[indice1].size(); i++)
            liste2.push_back(listeD[indice1][i]);
	      }

	      else if (sizeM2 == 2){
          indice1 = stoi(mots2[0]);
          indice2 = stoi(mots2[1]);
          for(int i(0); i < listeD[indice1].size(); i++)
            liste2.push_back(listeD[indice1][i]);
          int sizeL2 =  liste2.size();
          for(int i(0); i < listeD[indice2].size(); i++){
            test = true;
            for(int j(0); j < liste2.size(); j++){
              if (listeD[indice2][i] == liste2[j]){
                test = false;
                break;
              }
            }
            if(test)
              liste2.push_back(listeD[indice2][i]);
          }
	      }


        scoreTransition = getScoreTransition(liste1, liste2);
        this->scoreParVignette[i] = scoreTransition;
        mots1 = mots2;
        sizeM1 = sizeM2;

      }
      int score(0);
      for(int i(0); i < this->scoreParVignette.size(); i++)
        score += this->scoreParVignette[i];
      return score;
}




/* Méthode qui sert à la formation d'une sous chaîne
Entrée : Une chaine de caractères, un délimitateur, une chaine résultat
Action : Découpe une chaine de caractères.
Retourne : void
*/
void MyChecker::split(const std::string &chaine, char delimiteur, vector<string> &elements){
    stringstream ss(chaine);
    string sousChaine;
    while (std::getline(ss, sousChaine, delimiteur))
        elements.push_back(sousChaine);
}


/* Méthode qui sert à la formation d'une sous chaîne
Entrée : Une chaine de caractères, un délimitateur
Action : Découpe une chaine de caractères.
Retourne : chaine de caractères
*/
vector<string> MyChecker::split(const string &chaine, char delimiteur) {
    vector<string> mots;
    split(chaine, delimiteur, mots);
    return mots;
}


/* Méthode qui sert à la lecture des résultarts, résultats consignés dans
un fichier.
Entrée : Le nom du fichier à lire et le pourcentage.
Action : Extraire les données.
Retourne : void.
*/
void MyChecker::lectureFichier(string const nom_fichier, vector<vector<string>> listeD){

    std::ifstream fichier;
    fichier.open(nom_fichier.c_str());
    int indice1(0);
    int indice2(0);
    vector<string> liste1;
    vector<string> liste2;
    bool test(true);
    string ligne;
    int scoreTransition;
    vector<string> mots1;
    vector<string> mots2;


    if (fichier.is_open()) {

      getline(fichier, ligne);
      mots1 = split(ligne, ' ');

	    this->nbVignettes = stoi(mots1[0]);
      this->scoreParVignette = vector<int>(this->nbVignettes - 1, 0);

      getline(fichier, ligne);
      mots1 = split(ligne, ' ');


      for (int i(0); i < (this->nbVignettes -1); i++) {
        liste1.clear();
        liste2.clear();
	      getline(fichier, ligne);
        mots2 = split(ligne, ' ');

        if (mots1.size() == 1){
          indice1 = stoi(mots1[0]);
          for(int i(0); i < listeD[indice1].size(); i++)
            liste1.push_back(listeD[indice1][i]);
	      }

	      else if (mots1.size() == 2){
          indice1 = stoi(mots1[0]);
          indice2 = stoi(mots1[1]);
          for(int i(0); i < listeD[indice1].size(); i++)
            liste1.push_back(listeD[indice1][i]);
          for(int i(0); i < listeD[indice2].size(); i++){
            test = true;
            for(int j(0); j < liste1.size(); j++){
              if (listeD[indice2][i] == liste1[j]){
                test = false;
                break;
              }
            }
            if(test)
              liste1.push_back(listeD[indice2][i]);
          }
	      }


        if (mots2.size() == 1){
          indice1 = stoi(mots2[0]);
          for(int i(0); i < listeD[indice1].size(); i++)
            liste2.push_back(listeD[indice1][i]);
	      }

	      else if (mots2.size() == 2){
          indice1 = stoi(mots2[0]);
          indice2 = stoi(mots2[1]);
          for(int i(0); i < listeD[indice1].size(); i++)
            liste2.push_back(listeD[indice1][i]);
          int sizeL2 =  liste2.size();
          for(int i(0); i < listeD[indice2].size(); i++){
            test = true;
            for(int j(0); j < sizeL2; j++){
              if (listeD[indice2][i] == liste2[j]){
                test = false;
                break;
              }
            }
            if(test)
              liste2.push_back(listeD[indice2][i]);
          }
	      }


        scoreTransition = getScoreTransition(liste1, liste2);
        this->scoreParVignette[i] = scoreTransition;
        mots1 = mots2;

      }
    }
}
