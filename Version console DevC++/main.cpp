#include <iostream>
#include <ctime>
#include "Solution.h"
#include "Problem.h"
#include "SetUpParams.h"
#include "bench.h"
#include "MyAlgorithm.h"

Fonction choixFonction(int&xmin, int&xmax)
{
	std::cout<<"1. Ackley"<<std::endl;
	std::cout<<"2. Rastrigin"<<std::endl;
	std::cout<<"3. Rosenbrock"<<std::endl;
	std::cout<<"4. Schwefel"<<std::endl;
	std::cout<<"5. Schaffer"<<std::endl;
	std::cout<<"6. Weierstrass"<<std::endl;
	std::cout<<"Choix de la fonction : ";
	int choix;
	std::cin>>choix;
	while(1>choix || choix>6) std::cin>>choix;
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
		xmin=-5;
		xmax=10;
		return somme_rosenbrock;
	}
	if (choix==4)
	{
		xmin=-500;
		xmax=500;
		return schwefel;
	}
	if (choix==5)
	{
		xmin=-100;
		xmax=100;
		return schaffer;
	}
	if (choix==6)
	{
		xmin=-10;
		xmax=10;
		return weierstrass;
	}
	xmin=-5;
		xmax=10;
		return somme_rosenbrock;
}

int nbIte()
{
	std::cout<<"Nombre d'Iteration (30) : ";
	int i;
	std::cin>>i;
	while(i<1 || i>30) std::cin>>i;
	return i;
	return 1;
}

int nbEvo()
{
	std::cout<<"Nombre d'Evolution (66 666): ";
	int i;
	std::cin>>i;
	while(i<1) std::cin>>i;
	return i;
}

int nbMaxTrial()
{
	/*std::cout<<"Nombre d'essais avant de renouveler une solution (100) : ";
	int i;
	std::cin>>i;
	while(i<1 || i>100) std::cin>>i;
	return i;*/
	return 100;
}

int main(int argc, char** argv) {
	srand(time(0));
	
	int xmin,xmax;
	Fonction F=choixFonction(xmin,xmax);
	Problem P(xmin, xmax, 30, F);
	
	//SetUpParams(int nbRuns = 30, int nbEvoSteps = 2000000, int popSize = 30, int solSize = 30);
	//30,5000,30,30
	int iT=nbIte();
	int eVo=nbEvo();
	int maxTrial=nbMaxTrial();
	SetUpParams sup{iT, eVo, 30, 30,maxTrial};
	ABC A{P,sup};
	A.evolution();
	system("pause");
}
