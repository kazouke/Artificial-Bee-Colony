#include <iostream>
#include <ctime>
#include "Solution.h"
#include "Problem.h"
#include "SetUpParams.h"
#include "bench.h"
#include "MyAlgorithm.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/* Test pour Github - ICI C'EST LE MASTER*/

Fonction F=somme_rastrigin;

int main(int argc, char** argv) {
	srand(time(0));
	
	Problem P(10, 100, 30, F);
	//SetUpParams(int nbRuns 30, int nbEvoSteps 3000, int popSize 30, int solSize 30);
	SetUpParams sup{1, 1, 30, 30};
	
	ABC A{P,sup};
	A.evolution();
	//Revoir Banch manquants ?
	return 0;
}
