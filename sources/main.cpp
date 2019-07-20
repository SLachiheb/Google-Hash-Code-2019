#include "Data.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include "PresentationSimple.h"
#include "MyChecker.h"
#include "PresentationExacte.h"

using namespace std;

int main(int argc,char**argv){

  if(argc!=4){
    cerr <<" Veuillez saisir : " << argv[0] << "    <Numéro de méthode souhaitée>    <nom ficher (.txt)>     <pourcentage>" << endl;
    cerr <<"   Les numéros de méthodes associés sont : " << endl;
    cerr <<"    0 : méthode sens de lecture du fichier." << endl;
    cerr <<"    1 : méthode gloutonne." << endl;
    cerr <<"    2 : méthode métha-heuristique." << endl;
    cerr <<"    3 : méthode exacte PLNE "<< endl;
    cerr <<"    4 : méthode méthode heuristique d'arrondi PL "<< endl;

    return 1;
  }

  string numMethode;
  string nomFichier;
  double pourcent;

  numMethode = argv[1];
  nomFichier = argv[2];
  pourcent = atof(argv[3]);


  Data donnees;
  donnees.lectureFichier(nomFichier, pourcent);
  cout << "Lecture fichier " << pourcent << "%" << endl;
//  donnees.affichage();
  vector<vector<string>> listeDonnees = donnees.getListeD();
  PresentationSimple presentation;
  MyChecker checker;
  int score(0);
  srand(time(0));



  // Execution de la présentation la plus simple de l'exercice 1  :

if (numMethode == "0"){
  clock_t start, end;
  double elapsed;
  start = clock();
  presentation.donnePresentationSimple(donnees);
  end = clock();
  elapsed = ((double)end - start) / CLOCKS_PER_SEC;

  cout << "Présentation simple : " << endl;
  cout << "Calcul du score méthode simple > " << endl;
  vector<vector<string>>  presentationSimple = presentation.getPresentation();
  donnees.createFilePresentation("presentation.sol", presentationSimple);
  score = checker.scorePresentation("presentation.sol", listeDonnees);
  cout << " Score de : " << score << "." << endl;
  cout << " Pour un temps de : " << elapsed << "." << endl;
}


  // Execution du glouton améliorer de l'exercice 2 :

  if (numMethode == "1"){
    clock_t start, end;
    double elapsed;
    start = clock();
    presentation.presentationGlouton(donnees);
    end = clock();
    elapsed = ((double)end - start) / CLOCKS_PER_SEC;

    vector<vector<string>>  presentationGlou = presentation.getPresentation();
    donnees.createFilePresentation("presentationGlouton.sol", presentationGlou);
    cout << "Calcul du score méthode gloutonne > " << endl;
    score = checker.scorePresentation("presentationGlouton.sol", listeDonnees);
    cout << " Score de : " << score << "." << endl;
    cout << " Pour un temps de : " << elapsed << "." << endl;
  }


  // Execution de la méthaheuristique de l'exercice 3 question 1 :

  if (numMethode == "2"){
    clock_t start, end;
    double elapsed;
    start = clock();
    presentation.presentationMetha(donnees);
    end = clock();
    elapsed = ((double)end - start) / CLOCKS_PER_SEC;

    vector<vector<string>>  presentationMetha = presentation.getPresentation();
    donnees.createFilePresentation("presentationMetha.sol", presentationMetha);
    cout << "Calcul du score méthode méthaheuristique > " << endl;
    score = checker.scorePresentation("presentationMetha.sol", listeDonnees);
    cout << " Score de : " << score << "." << endl;
    cout << " Pour un temps de : " << elapsed << "." << endl;
  }


  // Execution de la méthaheuristique améliorer de l'exercice 3 question 2 :
/*  if (numMethode == "2"){
    clock_t start, end;
    double elapsed;
    start = clock();
    presentation.troisOptimisation(presentationMetha,  presentationMetha.size(), donnees, score);
    end = clock();
    elapsed = ((double)end - start) / CLOCKS_PER_SEC;

    vector<vector<string>>  presentationMethaAmeliore = presentation.getPresentation();
    donnees.createFilePresentation("presentationMethaAmeliore.sol", presentationMethaAmeliore);
    cout << "Calcul du score méthode méthaheuristique améliorer! > " << endl;
    score = checker.scorePresentation("presentationMethaAmeliore.sol", listeDonnees);
    cout << "Score de : " << score << "." << endl;
    cout << "Pouds un temps de : " << elapsed << "." << endl;
  }
*/
  // Execution de la méthode exacte inspiré du TSP :
  if (numMethode == "3"){
    PresentationExacte presentationE;
    clock_t start, end;
    double elapsed;
    start = clock();
    presentationE.plne(donnees);
    end = clock();
    elapsed = ((double)end - start) / CLOCKS_PER_SEC;
    vector<vector<string>>  presentationExacte = presentationE.getPresentation();

    donnees.createFilePresentation("presentationExacte.sol", presentationExacte);
    cout << "Calcul du score méthode exacte > " << endl;
    score = checker.scorePresentation("presentationExacte.sol", listeDonnees);
    cout << " Score de : " << score << "." << endl;
    cout << " Pour un temps de : " << elapsed << "." << endl;
  }


  // Execution de la méthode exacte par arrondi :
  if (numMethode == "4"){
    clock_t start, end;
    double elapsed;
    PresentationExacte presentationE;
    start = clock();
    presentationE.plne_arrondi(donnees);
    end = clock();
    elapsed = ((double)end - start) / CLOCKS_PER_SEC;

    vector<vector<string>>  presentationExacteArrondi = presentationE.getPresentation();
    donnees.createFilePresentation("presentationExacteArrondi.sol", presentationExacteArrondi);
    score = checker.scorePresentation("presentationExacteArrondi.sol", listeDonnees);
    cout << "Calcul du score méthode heuristique d'arrondi > " << endl;
    cout << " Score de : " << score << "." << endl;
    cout << " Pour un temps de : " << elapsed << "." << endl;
  }
  return 0;
}
