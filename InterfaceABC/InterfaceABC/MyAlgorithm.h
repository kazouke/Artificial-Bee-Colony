#ifndef MYALGORITHM_H
#define MYALGORITHM_H
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>

#include "Problem.h"
#include "SetUpParams.h"
#include "Solution.h"


using std::vector;
using std::ostream;
using std::istream;

struct particle
{
	int index;
	double fitness;
};

class ABC
{
public:
	ABC(const Problem& pbm, const SetUpParams& setup); 											//	OK
	~ABC();																						//	OK

	//-----------------Get----------------------------------------
	const vector<Solution*>& solutions() const;													//	OK	
	vector<struct particle>&  fitness_values();													//	OK	
	Solution& solution(const int index) const;													//	OK	
	double fitness(const int index) const;														//	OK	
	int upper_cost() const;																		//	OK	->Peu utile car les valeurs sont triées
	int lower_cost() const;																		//	OK	->Peu utile car les valeurs sont triées
	double best_cost() const;																	//	OK	->Peu utile car les valeurs sont triées
	double worst_cost() const;																	//	OK	->Peu utile car les valeurs sont triées
	Solution& best_solution() const;															//	OK	
	Solution& worst_solution() const;															//	OK	
	const SetUpParams& setup() const;															//	OK	retourne les paramètres

	//-----------------Boucle---------------------------------------
	double evolution(int info);																			//	OK	Boucle principale
	void initialize();																			//	OK	Renouvelle les solutions, calcule la fitness associée et les tri croissant par fitness
	void sendEmployedBees();																	//	OK
	void SendOnLookerBees(std::vector <int> probabilite);										//	OK
	std::vector <int> CalculateProbabilities() const;											//	OK
	void sendScoutBees();																		//	OK
	void evaluate();																			//	OK








private:
	vector<Solution*> 		d_solutions;     													//		Abeilles 				d_setup.population_size
	vector<struct particle> d_fitnessValues;													//		Evaluation des abeilles	d_setup.population_size
	const SetUpParams 		d_setup;															//		Parametres
	int 					d_upperCost, d_lowerCost;											//		Position de la meilleur / pire fitness->Peu utile car les valeurs sont triées

	void trier();
	void Propre(int param2change, int i);														//	OK	QuickSort
	int partition(int gauche, int droite);														//	OK	QuickSort
	void QuickSort(int gauche, int droite);														//	OK	QuickSort
};

#endif
