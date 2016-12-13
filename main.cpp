#include <iostream>
#include <ctime>
#include "Solution.h"
#include "Problem.h"
#include "SetUpParams.h"
#include "bench.h"
#include "MyAlgorithm.h"

Fonction F=somme_ackley;

Fonction choixFonction(int&xmin, int&xmax)
{
	std::cout<<"1. Ackley"<<std::endl;
	std::cout<<"2. Rastrigin"<<std::endl;
	std::cout<<"3. Rosenbrock"<<std::endl;
	std::cout<<"Choix de la fonction : ";
	int choix;
	std::cin>>choix;
	while(1>choix || choix>3) std::cin>>choix;
	if (choix==1)
	{
		xmin=-32.768;
		xmax=32.768;
		return somme_ackley;
	}
	if (choix==2)
	{
		xmin=-5.12;
		xmax=5.12;
		return somme_rastrigin;
	}
	if (choix==3)
	{
		xmin=-30;
		xmax=30;
		return somme_rosenbrock;
	}
}

int nbIte()
{
	std::cout<<"Nombre d'Iteration (max 30) : ";
	int i;
	std::cin>>i;
	while(i<1 || i>30) std::cin>>i;
	return i;
}

int nbEvo()
{
	std::cout<<"Nombre d'Evolution : ";
	int i;
	std::cin>>i;
	while(i<1) std::cin>>i;
	return i;
}

int main(int argc, char** argv) {
	srand(time(0));
	
	int xmin,xmax;
	F=choixFonction(xmin,xmax);
	Problem P(xmin, xmax, 30, F);
	
	//SetUpParams(int nbRuns 30, int nbEvoSteps 2000000, int popSize 30, int solSize 30);
	//30,5000,30,30
	int iT=nbIte();
	int eVo=nbEvo();
	SetUpParams sup{iT, eVo, 30, 30};
	ABC A{P,sup};
	double best=0;
	if (iT==eVo && eVo==1) best=A.evolution(2);
	else best=A.evolution(1);
	
	std::cout<<"Best cost "<<best<<std::endl;
	system("pause");
}

/*
A FAIRE
-Revoir les fonctions (manquantes, bug)
-S'approcher de fitness 0 à 0.001 prêt en moyenne
-Revoir les proba, proba négative DANGER
*/
