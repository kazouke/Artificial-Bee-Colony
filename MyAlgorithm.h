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
		ABC(const Problem& pbm,const SetUpParams& setup); 											//	OK
		~ABC();																						//	OK

		friend 	ostream& operator<< (ostream& os, const ABC& myAlgo);								//	OK	A voir si utile
		const SetUpParams& setup() const;															//	OK	retourne les paramètres
		void initialize();																			//	OK	Renouvelle les solutions, calcule la fitness associée et les tri croissant par fitness

		void evaluate();																			//	-	En cours

		const vector<Solution*>& solutions() const;													//	OK	
		int upper_cost() const;																		//	OK	->Peu utile car les valeurs sont triées
		int lower_cost() const;																		//	OK	->Peu utile car les valeurs sont triées
		Solution& solution(const int index) const;													//	OK	
		vector<struct particle>&  fitness_values();													//	OK	
		double fitness(const int index) const;														//	OK	

		double best_cost() const;																	//	OK	->Peu utile car les valeurs sont triées
		double worst_cost() const;																	//	OK	->Peu utile car les valeurs sont triées
		Solution& best_solution() const;															//	OK	
		Solution& worst_solution() const;															//	OK	

		double evolution();																			//	-	En attente d'évolution
		void trier();																				//	OK	QuickSort
		
		void sendEmployedBees();
		std::vector <int> CalculateProbabilities() const;
		void SendOnLookerBees(std::vector <int> probabilite);
		void sendScoutBees();

	private:
		vector<Solution*> 		d_solutions;     													//		nombre d'abeille d_setup.solution_size
		vector<struct particle> d_fitnessValues;													//		
		const SetUpParams 		d_setup;															//		
		int 					d_upperCost,d_lowerCost;											//		Position de la meilleur / pire fitness->Peu utile car les valeurs sont triées
		
		int partition(int gauche, int droite);														//	OK	QuickSort
		void QuickSort(int gauche, int droite);														//	OK	QuickSort										
};

#endif
