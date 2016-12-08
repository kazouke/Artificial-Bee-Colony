#include <iostream>
#include <ctime>
#include "Solution.h"
#include "Problem.h"
#include "SetUpParams.h"
#include "bench.h"
#include "MyAlgorithm.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/* Test pour Github - ICI C'EST LE MASTER*/

Fonction F=somme_sphere;

int main(int argc, char** argv) {
	srand(time(0));
	//Problem(double lowLim, double upLim, int dim, Fonction f);
	Problem P(-5.12, 5.12, 30, F);
	//SetUpParams(int nbRuns 30, int nbEvoSteps 2000000, int popSize 30, int solSize 30);
	SetUpParams sup{30, 5000, 30, 30};
	
	ABC A{P,sup};
	double best=A.evolution();
	std::cout<<"Best cost "<<best;
	//Revoir Banch manquants ?
	
}
