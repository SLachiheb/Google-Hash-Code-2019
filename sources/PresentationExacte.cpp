#include "Data.h"
#include "MyChecker.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <time.h>
#include <stdio.h>
#include "MyChecker.h"
#include <ilcplex/ilocplex.h>
#include "PresentationExacte.h"
#include <algorithm>

using namespace std;


/* Méthode qui sert à la comparaison d'élément de type pair
Entrées : Les deux pairs à comparer.
Action : Comparaison pour extraire le plus grand, true si oui et false sinon.
Retourne : un booléen .
*/
struct myclass {
  bool operator() (pair<int, double> i, pair<int, double> j) { return (i.second > j.second );}
} myobject;



/* Constructeur */
PresentationExacte::PresentationExacte(){
}


/* Getter utilisé pour récupéré la présentation formée par un des deux programmes linéaire.
Entrée : /
Action : Récupération de données.
Retourne : la présentation sous forme d'un vecteur 2D de caractères.
*/
vector<vector<string>>  PresentationExacte::getPresentation(){
  return this->presentation;
}



/* Méthode qui, par exécution d'un PLNE par flots permet l'exécution d'un eméthode
exacte dans le but de répondre à l'objectif d'une présentation optimale(que pour les H)
Entrée : Les données extraites du fichier
Action : Avoir un ordre optimal.
Retourne : void.
*/
void PresentationExacte::plne(Data donnees){
  MatriceCout(donnees);
  int somme = 0;
  vector< pair <int,int> > vect;
  vector<int> rest;
  for(int i(0); i < this->couts.size(); i++){
    somme = 0;
    for(int j(0); j < this->couts.size(); j++)
      somme += this->couts[i][j];
    if (somme != 0)
      vect.push_back( make_pair((vect.size()), i));
    else
      rest.push_back(i);
  }

  int nbInstances = vect.size() + 1;
  ILOSTLBEGIN
  IloEnv env;

  IloModel mod (env);

	typedef IloArray<IloNumVarArray> NumVarMatrix;
  typedef IloArray<NumVarMatrix> NumVar3Matrix;

	NumVarMatrix x_mn(env, nbInstances);
	for (int i(0); i < nbInstances; i++) {
		x_mn[i] =  IloNumVarArray(env, nbInstances);
		for (int j(0); j < nbInstances; j++) {
		    x_mn[i][j] = IloNumVar(env, 0, 1, ILOINT);
		}
	}


//  Contraintes TSP :


	for(int i(0); i < nbInstances; i++){
	  IloExpr contraint(env);
		for(int j(0); j < nbInstances; j++)
			contraint = contraint + x_mn[i][j];
		mod.add(contraint == 1);

	}



	for(int i(0); i < nbInstances; i++){
    IloExpr contraint(env);
		for(int j(0); j < nbInstances; j++)
			contraint += x_mn[j][i];
  	 mod.add(contraint == 1);
	}

  IloExpr contraint15(env);
  for(int i(0); i < nbInstances; i++){
    for(int j(0); j < nbInstances; j++){
      if (i == j)
        contraint15 += x_mn[i][j];
    }
  }
  mod.add(contraint15 == 0);

  IloExpr contraint16(env);
  for(int i(0); i < nbInstances; i++){
    for(int j(0); j < nbInstances; j++){
      if (i == j)
        contraint16 += x_mn[j][i];
    }
  }
  mod.add(contraint16 == 0);


  for(int i(0); i < nbInstances ; i++){
    for(int j(0); j < nbInstances ; j++){
        mod.add(x_mn[i][j] + x_mn[j][i] <= 1);
    }
  }



// Contraintes des sous tours

    NumVarMatrix z_ij(env, nbInstances);
    for (int i(0); i < nbInstances; i++){
      z_ij[i] =  IloNumVarArray(env, nbInstances);
      for (int j(0); j < nbInstances; j++) {
          z_ij[i][j] = IloNumVar(env, 0, IloInfinity, ILOFLOAT);
        }
      }

    IloExpr contraint4(env);
    for(int j(1); j < nbInstances; j++)
  		contraint4 += z_ij[0][j];
    mod.add(contraint4 == (nbInstances - 1));



    for(int i(1); i < nbInstances; i++){
      IloExpr contraint1(env);
      IloExpr contraint2(env);
      for(int j(1); j < nbInstances; j++){
        if (i != j)
          contraint1 += z_ij[i][j];
      }
      for(int j(0); j < nbInstances; j++){
        if (i != j)
          contraint2 += z_ij[j][i];
      }
      mod.add(((contraint1 + 1) - contraint2) == 0);
    }

/*
    IloExpr contraint5(env);
    for(int i(0); i < nbInstances; i++){
      for(int j(0); j < nbInstances; j++){
        if (i == j)
          contraint5 += z_ij[i][j];
      }
    }
    mod.add(contraint5 == 0);

    IloExpr contraint6(env);
    for(int i(0); i < nbInstances; i++){
      for(int j(0); j < nbInstances; j++){
        if (i == j)
          contraint6 += z_ij[j][i];
      }
    }
    mod.add(contraint6 == 0);
*/
    for(int i(0); i < nbInstances; i++){
      for(int j(1); j < nbInstances; j++)
        if (i != j)
          mod.add( ((z_ij[i][j] + z_ij[j][i]) - ((nbInstances - 1) * (x_mn[i][j] + x_mn[j][i])) ) <= 0);
    }

  // Fonction objectif à maximiser :
  IloExpr expr(env);
  for(int i(0); i < nbInstances - 1; i++){
		for(int j(0); j < nbInstances  - 1;j++){
			expr += x_mn[i][j] * this->couts[vect[i].second][vect[j].second];
		}
  }

  mod.add(IloMinimize(env, expr));

//  cout << mod << endl;

  IloCplex cplex(mod);
  cplex.setOut(env.getNullStream());
  cplex.solve();
  double objval = cplex.getObjValue();


  vector<int> tourOpt(nbInstances);
  tourOpt[0] = 0;
  int h(nbInstances - 1);
  for(int i(1); i < nbInstances + 1; i++){
    for(int j(0); j < nbInstances + 1; j++){
      if (cplex.getValue(x_mn[h][j]) > 0.5){
        tourOpt[i] = vect[j].second;
        h = j;
        break;
      }
    }
  }
  for(int i(0); i < rest.size(); i++)
    tourOpt.push_back(rest[i]);

    this->presentation = vector<vector<string>> (tourOpt.size());
    for(int i(1); i < tourOpt.size() ; i++){
      this->presentation[i] = vector<string>(2);
      this->presentation[i][0] = to_string(tourOpt[i]);
    }

  env.end();
}







/* Méthode qui, par exécution d'un PL par flots permet l'exécution d'un eméthode
par arrondi dans le but de répondre à l'objectif d'une présentation heuristique
(que pour les H)
Entrée : Les données extraites du fichier
Action : Avoir un ordre heuristique par arrondi.
Retourne : void.
*/

void PresentationExacte::plne_arrondi(Data donnees){
  MatriceCout(donnees);
  int somme = 0;
  vector< pair <int,int> > vect;
  vector<int> rest;
  for(int i(0); i < this->couts.size(); i++){
    somme = 0;
    for(int j(0); j < this->couts.size(); j++)
      somme += this->couts[i][j];
    if (somme != 0)
      vect.push_back( make_pair((vect.size()-1), i));
    else
      rest.push_back(i);
  }
  int nbInstances = vect.size() + 1;
  vect.push_back( make_pair((vect.size()-1), 4));

  ILOSTLBEGIN
  IloEnv env;

  IloModel mod (env);

	typedef IloArray<IloNumVarArray> NumVarMatrix;
  typedef IloArray<NumVarMatrix> NumVar3Matrix;

  NumVarMatrix x_mn(env, nbInstances);
	for (int i(0); i < nbInstances; i++) {
		x_mn[i] =  IloNumVarArray(env, nbInstances);
		for (int j(0); j < nbInstances; j++) {
		    x_mn[i][j] = IloNumVar(env, 0, IloInfinity, ILOFLOAT);
		}
	}


//  Contraintes TSP :


	for(int i(0); i < nbInstances; i++){
	  IloExpr contraint(env);
		for(int j(0); j < nbInstances; j++)
			contraint = contraint + x_mn[i][j];

		mod.add(contraint == 1);
	}



	for(int i(0); i < nbInstances; i++){
    IloExpr contraint(env);
		for(int j(0); j < nbInstances; j++)
			contraint += x_mn[j][i];

		mod.add(contraint == 1);
	}





/*
  IloExpr contraint15(env);
  for(int i(0); i < nbInstances; i++){
    for(int j(0); j < nbInstances; j++){
      if (i == j)
        contraint15 += x_mn[i][j];
    }
  }
  mod.add(contraint15 == 0);

  IloExpr contraint16(env);
  for(int i(0); i < nbInstances; i++){
    for(int j(0); j < nbInstances; j++){
      if (i == j)
        contraint16 += x_mn[j][i];
    }
  }
  mod.add(contraint16 == 0);
*/

// Contraintes des sous tours

    NumVarMatrix z_ij(env, nbInstances);
    for (int i(0); i < nbInstances; i++){
      z_ij[i] =  IloNumVarArray(env, nbInstances);
      for (int j(0); j < nbInstances; j++) {
          z_ij[i][j] = IloNumVar(env, 0, IloInfinity, ILOFLOAT);
        }
      }

    IloExpr contraint4(env);
    for(int j(1); j < nbInstances; j++)
  		contraint4 += z_ij[0][j];
    mod.add(contraint4 == (nbInstances - 1));



    for(int i(1); i < nbInstances; i++){
      IloExpr contraint1(env);
      IloExpr contraint2(env);
      for(int j(1); j < nbInstances; j++){
        if (i != j)
          contraint1 += z_ij[i][j];
      }
      for(int j(0); j < nbInstances; j++){
        if (i != j)
          contraint2 += z_ij[j][i];
      }
      mod.add(((contraint1 + 1) - contraint2) == 0);
    }


    IloExpr contraint5(env);
    for(int i(0); i < nbInstances; i++){
      for(int j(0); j < nbInstances; j++){
        if (i == j)
          contraint5 += z_ij[i][j];
      }
    }
    mod.add(contraint5 == 0);

    IloExpr contraint6(env);
    for(int i(0); i < nbInstances; i++){
      for(int j(0); j < nbInstances; j++){
        if (i == j)
          contraint6 += z_ij[j][i];
      }
    }
    mod.add(contraint6 == 0);

    for(int i(0); i < nbInstances; i++){
      for(int j(1); j < nbInstances; j++)
        if (i != j)
          mod.add( ((z_ij[i][j] + z_ij[j][i]) - ((nbInstances - 1) * (x_mn[i][j] + x_mn[j][i])) ) <= 0);
    }

  // Fonction objectif à maximiser :
  IloExpr expr(env);
  for(int i(0); i < nbInstances - 1; i++){
		for(int j(0); j < nbInstances  - 1;j++){
			expr += x_mn[i][j] * this->couts[vect[i].second][vect[j].second];
		}
  }

  mod.add(IloMinimize(env, expr));

  //cout << mod << endl;

  IloCplex cplex(mod);
  cplex.setOut(env.getNullStream());
  cplex.solve();

  double objval = cplex.getObjValue();

  vector<vector<pair<int, double>>> tmp(nbInstances);
  for(int i(0); i < nbInstances ; i++){
    tmp[i] = vector<pair<int,double>>(nbInstances);
    for(int j(0); j < nbInstances; j++)
        tmp[i][j] = make_pair(j, cplex.getValue(x_mn[i][j]));

  }

  vector<int> tourOpt(nbInstances);
  tourOpt[0] = 0;
  int h(nbInstances-1);
  vector<pair<int, double>> copie;
  for(int j(0); j < tmp.size(); j++)
        tmp[j].erase(tmp[j].begin() + h);


  for(int i(1); i < nbInstances; i++){

    for(int j(0); j < tmp.size(); j++){
      for(int k(0); k < tmp[i].size(); k++){
        if (tmp[j][k].first == h)
          tmp[j].erase(tmp[j].begin() + k);
      }
    }

    copie = tmp[h];
    sort(copie.begin(), copie.end(), myobject);
    tourOpt[i] = vect[copie[0].first].second;
    h = (int)copie[0].first;
  }

  for(int i(0); i < rest.size(); i++)
    tourOpt.push_back(rest[i]);

  this->presentation = vector<vector<string>> (tourOpt.size());
  for(int i(1); i < tourOpt.size() ; i++){
    this->presentation[i] = vector<string>(2);
    this->presentation[i][0] = to_string(tourOpt[i]);
  }

  env.end();
}




/* Méthode qui sert au calcul d'une matrice coût servant aux programmes linéaire.
Entrée : Les données Data du fichier.
Action : Calculer un matrice des couts des transitions.
Retourne : void.
*/
void PresentationExacte::MatriceCout(Data donnees){
    vector<vector<string>> listeD = donnees.getListeD();
    MyChecker c;
    vector<string> liste1, liste2;
    this->couts = vector<vector<int>>(listeD.size());

    for(int i(0); i < listeD.size(); i++){
      this->couts[i] = vector<int>(listeD.size());
      liste1.clear();
      for(int k(0); k < listeD[i].size(); k++)
        liste1.push_back(listeD[i][k]);

      for(int j(0); j < listeD.size(); j++){
        liste2.clear();
        for(int k(0); k < listeD[j].size(); k++)
          liste2.push_back(listeD[j][k]);
        this->couts[i][j] = -c.getScoreTransition(liste1, liste2);
      }
    }
}
