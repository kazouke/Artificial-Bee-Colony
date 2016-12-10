#include <iostream>
#include <ctime>
#include "Solution.h"
#include "Problem.h"
#include "SetUpParams.h"
#include "bench.h"
#include "MyAlgorithm.h"

Fonction F=somme_sphere;

int main(int argc, char** argv) {
	srand(time(0));
	//Problem(double lowLim, double upLim, int dim, Fonction f);
	Problem P(-5.12, 5.12, 30, F);
	//SetUpParams(int nbRuns 30, int nbEvoSteps 2000000, int popSize 30, int solSize 30);
	//30,5000,30,30
	SetUpParams sup{30, 5000, 30, 30};
	
	ABC A{P,sup};
	double best=A.evolution();
	std::cout<<"Best cost "<<best;
	system("pause");
}

/*
A FAIRE
-Revoir les fonctions (manquantes, bug)
-S'approcher de fitness 0 à 0.001 prêt en moyenne
-Revoir les proba, proba négative DANGER
*/
