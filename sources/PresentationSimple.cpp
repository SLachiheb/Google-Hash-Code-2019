#include "Data.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <time.h>
#include<stdio.h>
#include "MyChecker.h"
#include <algorithm>
#include <limits>
#include "PresentationSimple.h"
using namespace std;


/* Dans ce fichier sont présentes les méthodes dites "simple" tels que la
présentation dans le sens de lecture, la méthode gloutonne et la
méthode par métha heuristique.

Les méthodes présentes dans ce fichier sont ;

  PresentationSimple();

  void donnePresentationSimple(Data);
  void presentationGlouton(Data);
  void presentationMetha(Data);

  vector<vector<string>> troisOptimisation(vector<vector<string>>, int, Data, int);

  vector<vector<string>>  getPresentation();
  bool haveCommun(vector<string>, vector<string>);


*/


/* Constructeur */
PresentationSimple::PresentationSimple(){

}


/* Méthode qui sert à la formation d'une présentation par sens de lecture
Entrée : Les données "Data" du fichier
Action : Dans le sens de lecture, affiche toutes les images de type "H"
puis toutes celles de type "V".
Retourne : void
*/

void PresentationSimple::donnePresentationSimple(Data donnee){
  vector<vector<string>> listeH = donnee.getListeH();
  vector<vector<string>> listeV = donnee.getListeV();
  int sizeH = listeH.size();
  int sizeV = listeV.size();

  if(sizeV%2 != 0){
    listeV.pop_back();
    sizeV--;
  }

  this->presentation = vector<vector<string>>(sizeH + (sizeV/2));
  for(int i(0) ; i < sizeH; i++){
    this->presentation[i] = vector<string>(2);
    this->presentation[i][0] = listeH[i][0];
  }

  int i(0);
  while (i < sizeV/2){
    this->presentation[i + sizeH] = vector<string>(2);
    this->presentation[i + sizeH][0] = listeV[i * 2][0];
    this->presentation[i + sizeH][1] = listeV[(i * 2) + 1][0];
    i += 1;
  }
}




/* Méthode qui sert afficher une présentation
Entrée : /
Action : afficher
Retourne : void
*/
void PresentationSimple::afficher(){
  for(int i(0); i < this->presentation.size(); i++){
    for(int j(0); j < this->presentation[i].size(); j++){
      cout << this->presentation[i][j] << " " ;
    }
    cout << endl;
  }
}





/* Méthode qui sert à la formation d'une présentation par un algorithme
glouton avec plusieurs amélioration qui permettent d'aller plus rapidement.
Entrée : Les données "Data" du fichier
Action : Prend au hasar une image et lui fait succéder la meilleur des "H"
ou "V". Si c'est une "H" on recommence, si c'est une "V", on cherche le
meilleur binome.
Retourne : void
*/

void PresentationSimple::presentationGlouton(Data donnees){
  this->presentation.clear();
  vector<vector<string>> listeH = donnees.getListeH();
  vector<vector<string>> listeV = donnees.getListeV();
  vector<vector<string>> listeD = donnees.getListeD();

  if (listeV.size()%2 != 0)
    listeV.pop_back();
  this->presentation = vector<vector<string>>(listeH.size() + (listeV.size()/2));
  srand(time(0));
  float alea = ((float)rand() / (float)RAND_MAX);
  if (listeH.size() == 0)
    alea = 1;
  if (listeV.size() == 0)
    alea = 0;
  int indice1(-1);
  int indice2(-1);
  vector<string> liste1;
  vector<string> liste2;
  vector<string> tmp;
  bool test(true);
  MyChecker calculScore;
  int val(0);
  int nb = 2;
  int scoreMax = 0;

  if (alea <= 0.50){
    srand(time(0));
    indice1 = rand()%listeH.size();
    this->presentation[0] = vector<string>(2);
    this->presentation[0][0] = listeH[indice1][0];
    for(int i(1); i < listeH[indice1].size(); i++)
      liste1.push_back(listeH[indice1][i]);
    listeH.erase(listeH.begin() + indice1);
  }
  if (alea > 0.50){
    srand(time(0));
    indice1 = rand()%listeV.size();
    indice2 = rand()%listeV.size();
    while (indice1 == indice2)
      indice2 = rand()%listeV.size();
    this->presentation[0] = vector<string>(2);
    this->presentation[0][0] = listeV[indice1][0];
    this->presentation[0][1] = listeV[indice2][0];
    for(int i(1); i < listeV[indice1].size(); i++)
      liste1.push_back(listeV[indice1][i]);
    for(int i(1); i < listeV[indice2].size(); i++){
      test = true;
      for(int j(1); j < liste2.size(); j++){
        if (listeV[indice2][i] == liste1[j]){
          test = false;
          break;
        }
      }
      if(test)
        liste1.push_back(listeV[indice2][i]);
    }
    listeV.erase(listeV.begin() + indice1);
    if(indice2 > indice1)
      listeV.erase(listeV.begin() + (indice2-1));
    else
      listeV.erase(listeV.begin() + indice2);
  }


  for (int p(1); p < (this->presentation.size()); p++){
    if (p%500==0)
      cout << "       >>>>  "<< p << " slides effectuées sur " << this->presentation.size() << "."<< endl;
    int cpt = 0;
    vector<int> scoreH(listeH.size());
    for(int j(0); j < listeH.size(); j++){
      liste2.clear();
      scoreMax = 0;
      for(int i(1); i < listeH[j].size(); i++)
        liste2.push_back(listeH[j][i]);
        if (scoreMax*nb >= liste1.size()){
          scoreH[j] = 0;
          break;
        }
        scoreH[j] = calculScore.getScoreTransition(liste1, liste2);
        if (scoreH[j] > scoreMax)
           scoreMax = scoreH[j];
      if (scoreH[j] >= (liste1.size() / nb)){
        break;
      }
    }
    int maxH(-1);
    int indiceMH(-1);
    for (int i(0); i < scoreH.size(); i++)
     if( scoreH[i] > maxH){
       maxH = scoreH[i];
       indiceMH = i;
     }

    vector<int> scoreV(listeV.size(), 0);
    for(int j(0); j < listeV.size(); j++){
       liste2.clear();
       for(int i(1); i < listeV[j].size(); i++)
         liste2.push_back(listeV[j][i]);
       scoreV[j] = calculScore.getScoreTransition(liste1, liste2);
       if (scoreV[j] >= (liste1.size() / nb)){
         break;
       }
     }
     int maxV(-1);
     int indiceMV(-1);
     for (int i(0); i < scoreV.size(); i++)
      if( scoreV[i] > maxV){
        maxV = scoreV[i];
        indiceMV = i;
      }


    if (maxH >= maxV){
      this->presentation[p] = vector<string>(2);
      this->presentation[p][0] = listeH[indiceMH][0];
      liste2.clear();
      for(int i(1); i <  listeH[indiceMH].size(); i++)
        liste2.push_back(listeH[indiceMH][i]);
      listeH.erase(listeH.begin() + indiceMH);
    }

    else {
      this->presentation[p] = vector<string>(2);
      this->presentation[p][0] = listeV[indiceMV][0];
      liste2.clear();
      for(int i(1); i <  listeV[indiceMV].size(); i++)
        liste2.push_back(listeV[indiceMV][i]);
      listeV.erase(listeV.begin() + indiceMV);
      scoreV.clear();
      scoreV.resize(listeV.size(), 0);
      tmp = liste2;
      scoreMax = 0;
      for(int j(0); j < listeV.size(); j++){
         liste2 = tmp;
         for(int i(1); i < listeV[j].size(); i++){
           test = true;
           for(int k(0); k < liste2.size(); k++){
             if (listeV[j][i] == liste2[k]){
               test = false;
               break;
             }
           }
           if(test)
             liste2.push_back(listeV[j][i]);
        }
        if (scoreMax*nb >= liste2.size()){
           scoreV[j] = 0;
           break;
         }
        scoreV[j] = calculScore.getScoreTransition(liste1, liste2);
        if (scoreV[j] > scoreMax)
           scoreMax = scoreV[j];
        if (scoreV[j] >= (liste1.size()) / nb){
          //break;
        }
      }
      maxV = -1;
      indiceMV = -1;
      for (int i(0); i < scoreV.size(); i++)
        if( scoreV[i] > maxV){
          maxV = scoreV[i];
          indiceMV = i;
      }
       this->presentation[p][1] = listeV[indiceMV][0];
       for(int i(1); i < listeV[indiceMV].size(); i++)
          liste2.push_back(listeV[indiceMV][i]);
       listeV.erase(listeV.begin() + indiceMV);
    }
    liste1.clear();
    liste1 = liste2;
  }
}





/* Méthode qui sert à la formation d'une présentation par une métha-heuristique
basée un algorithme génétique.
Entrée : Les données "Data" du fichier .
Action : On lance m fils de la meilleur présentaiton par mutation. La mutation
est d'échanger deux vignettes ou échanger deux images "V" de deux vignettes
différentes. On fait cela sur p générations
Retourne : void
*/


void PresentationSimple::presentationMetha(Data donnees){
  vector<vector<string>> listeV = donnees.getListeV();
  vector<vector<string>> newPresentation;
  cout << "Présentation glouton qui sert de base : "<<endl;
  presentationGlouton(donnees);
  cout << "Lancement de la métha-heuristique : "<<endl;
  newPresentation = this->presentation;

  MyChecker c;
  int score(0);
  int scoreOld(0);
  score = 0;
  score = c.scorePresentation(this->presentation, donnees.getListeD());
  cout << "Score de commencement :" << score <<endl;
  int indice1(-1);
  int indice2(-1);
  bool amelioration(false);
  vector<string> temp(2);
  string temp1;
  int it(0);
  int iteration(0);
  vector<vector<string>> echange1(3);
  vector<vector<string>> echange2(3);
  float alea;
  while(it < 100){
    it++;
    cout << "... " <<  "génération numéro : " << it << endl;
    amelioration = false;
    iteration = 0;
    while(iteration < 1000){
      iteration++;
      alea = ((float)rand() / (float)RAND_MAX);
      if(listeV.size() == 0)
        alea = 0.1;

      if (alea <= 0.50){ // On permutte 2 vignet tes.
        indice1 = (int)(((float)rand() / (float)RAND_MAX) * (this->presentation.size() - 1));
        indice2 = (int)(((float)rand() / (float)RAND_MAX) * (this->presentation.size() - 1));
        while (indice1 == indice2)
          indice2 = (int)(((float)rand() / (float)RAND_MAX) * (this->presentation.size() - 1));

        temp = newPresentation[indice2];
        newPresentation[indice2] = newPresentation[indice1];
        newPresentation[indice1] = temp;



        echange1.clear();
        if(indice2 != 0)
          echange1.push_back(newPresentation[indice2-1]);
        echange1.push_back(newPresentation[indice2]);
        if(indice2 != (this->presentation.size() - 1))
          echange1.push_back(newPresentation[indice2+1]);
        score = 0;
        score = c.scorePresentation(echange1, donnees.getListeD());
        echange2.clear();
        if(indice1 != 0)
          echange2.push_back(newPresentation[indice1-1]);
        echange2.push_back(newPresentation[indice1]);
        if(indice1 != (this->presentation.size() - 1))
          echange2.push_back(newPresentation[indice1+1]);
        score += c.scorePresentation(echange2, donnees.getListeD());


        echange1.clear();
        if(indice2 != 0)
          echange1.push_back(this->presentation[indice2-1]);
        echange1.push_back(this->presentation[indice2]);
        if(indice2 != (this->presentation.size() - 1))
          echange1.push_back(this->presentation[indice2+1]);
        scoreOld = 0;
        scoreOld = c.scorePresentation(echange1, donnees.getListeD());
        echange2.clear();
        if(indice1 != 0)
          echange2.push_back(this->presentation[indice1-1]);
        echange2.push_back(this->presentation[indice1]);
        if(indice1 != (this->presentation.size() - 1))
          echange2.push_back(this->presentation[indice1+1]);
        scoreOld += c.scorePresentation(echange2, donnees.getListeD());

      //  score = 0;
      //  score = c.scorePresentation(newPresentation, donnees.getListeD());

        if (score > scoreOld){
          this->presentation = newPresentation;
          scoreOld = score;
          amelioration = true;
        }
      }

      else{ // On permutte une des deux photos V dans deux vignettes.
        if (listeV.size() != 0){
          indice1 = (int)(((float)rand() / (float)RAND_MAX) * (this->presentation.size() - 1));
          while (newPresentation[indice1][1] == "")
            indice1 = (int)(((float)rand() / (float)RAND_MAX) * (this->presentation.size() - 1));
          indice2 = (int)(((float)rand() / (float)RAND_MAX) * (this->presentation.size() - 1));
          while (newPresentation[indice2][1] == "" && indice1 != indice2)
            indice2 = (int)(((float)rand() / (float)RAND_MAX) * (this->presentation.size() - 1));

            int v1 = (int) ((float)rand() / (float)RAND_MAX);
            int v2 = (int) ((float)rand() / (float)RAND_MAX);

            temp1 = newPresentation[indice2][v1];
            newPresentation[indice2][v1] = newPresentation[indice1][v2];
            newPresentation[indice1][v2] = temp1;

            echange1.clear();
            if(indice2 != 0)
              echange1.push_back(newPresentation[indice2-1]);
            echange1.push_back(newPresentation[indice2]);
            if(indice2 != (this->presentation.size() - 1))
              echange1.push_back(newPresentation[indice2+1]);
            score = 0;
            score = c.scorePresentation(echange1, donnees.getListeD());
            echange2.clear();

            if(indice1 != 0)
              echange2.push_back(newPresentation[indice1-1]);
            echange2.push_back(newPresentation[indice1]);
            if(indice1 != (this->presentation.size() - 1))
              echange2.push_back(newPresentation[indice1+1]);
            score += c.scorePresentation(echange2, donnees.getListeD());
            echange1.clear();

            if(indice2 != 0)
              echange1.push_back(this->presentation[indice2-1]);
            echange1.push_back(this->presentation[indice2]);
            if(indice2 != (this->presentation.size() - 1))
              echange1.push_back(this->presentation[indice2+1]);
            scoreOld = 0;
            scoreOld = c.scorePresentation(echange1, donnees.getListeD());
            echange2.clear();
            if(indice1 != 0)
              echange2.push_back(this->presentation[indice1-1]);
            echange2.push_back(this->presentation[indice1]);
            if(indice1 != (this->presentation.size() - 1))
              echange2.push_back(this->presentation[indice1+1]);
            scoreOld += c.scorePresentation(echange2, donnees.getListeD());
          //  score = c.scorePresentation(newPresentation, donnees.getListeD());


    //        score = 0;
    //        score = c.scorePresentation(newPresentation, donnees.getListeD());

            if (score > scoreOld){
              this->presentation = newPresentation;
              scoreOld = score;
              amelioration = true;

            }
        }
      }
      newPresentation = this->presentation;
    }
  }
}




/* Méthode qui sert à la formation d'une présentation par une métha-heuristique
basée un algorithme de voisinage.
Entrée : Les données "Data" du fichier .
Action : On lance un voisinage 2opt (ou 3opt) sur le meilleur trouvé et ainsi
de suite jusqu'à ce que l'on ne s'améliore plus. Non utilisée car trop lente.
Retourne : void
*/

vector<vector<string>> PresentationSimple::troisOptimisation(vector<vector<string>> presentation, int n, Data donnees, int oldScore) {
  vector<vector<vector<string>>> listePresentation;
	vector<vector<string>> tmp;
	tmp = presentation;
	vector<string> v1, v2, u1, u2, w1, w2;
  int score(0);
  MyChecker c;
  int indiceMax = -1;
  int newScore(1000000);
  int it(0);
	// Itération sur chaque arête

  while (newScore > oldScore){
    listePresentation.clear();
  	for (int i = 0; i < n - 5; i++){
  		presentation = tmp;
  		// first edge
  		u1 = presentation[i];
  		u2 = presentation[(i+1) % n];

  		// avec les aretes non adjacentes
  		for (int j = i + 2; j < n - 3; j++){
  		  presentation = tmp;
  			v1 = presentation[j % n];
  			v2 = presentation[(j+1) % n];

  				presentation = tmp;
        	int start = i + 1;
        	int end = j;
  				vector<string> temp;

        //	while (end - start > 0) {
      			temp = presentation[start % n];
      			presentation[start % n] = presentation[end % n];
      			presentation[end % n] = temp;
      			start++;
      			end--;
      		//}
  		//		start = j + 1;
      //    if( c.getScoreTransition)
          listePresentation.push_back(presentation);
  		}
  	}
    vector<int> listeScore(listePresentation.size());
    for(int i(0); i < listePresentation.size(); i++){
      listeScore[i] = c.scorePresentation(listePresentation[i], donnees.getListeD());
    }
    for (int i(0); i < listeScore.size(); i++)
      if( listeScore[i] > listeScore[indiceMax])
        indiceMax = i;
    if (it != 0)
      oldScore = newScore;

    newScore = c.scorePresentation(listePresentation[indiceMax], donnees.getListeD());
    it++;
    cout << it << endl;

  }

  if (it == 0)
    return this->presentation;
  else
    return listePresentation[indiceMax];
}




// Retourne la présentation formée par les différentes méthodes.
vector<vector<string>>  PresentationSimple::getPresentation(){
  return this->presentation;
}



/* Méthode utilisée pour une tentative d'amélioration du glouton en formant les
binome verticaux via leur ressemblances ou dissemblances.
*/
bool PresentationSimple::haveCommun(vector<string> liste1, vector<string> liste2){
  int size1 = liste1.size();
  int size2 = liste2.size();

  if (size1 > size2){
    for(int i(0); i < size1; i++){
      for(int j(0); j < size2; j++){
        if(liste1[i] == liste2[j])
          return true;
      }
    }
  } else {
    for(int i(0); i < size2; i++){
      for(int j(0); j < size1; j++){
        if(liste2[i] == liste1[j])
          return true;
      }
    }
  }
  return false;
}
