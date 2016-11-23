#ifndef MYALGORITHM_H
#define MYALGORITHM_H
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "Problem.h"
#include "SetUpParams.h"
#include "Solution.h"

using std::vector;
using std::ostream;
using std::istream;

struct particle // index of a particle in the swarm and its fitness
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
		friend 	istream& operator>> (istream& is, ABC& myAlgo);										//	-	En attente de SetUpParams
		//ABC& operator= (const ABC& myAlgo);														//	X	Inutile
		const SetUpParams& setup() const;															//	OK	retourne les paramètres
		void initialize();																			//	-	En attente de Solution

		// creates a array with fitness of all solutions in ABC and its position in the ABC
		void evaluate();																			//	X	

		const vector<Solution*>& solutions() const;													//	OK	
		int upper_cost() const;																		//	OK	->Peu utile car les valeurs sont triées
		int lower_cost() const;																		//	OK	->Peu utile car les valeurs sont triées
		Solution& solution(const int index) const;													//	OK	
		vector<struct particle>&  fitness_values();													//	OK	
		double fitness(const int index) const;														//	OK	

		double best_cost() const;																	//	OK	->Peu utile car les valeurs sont triées
		double worst_cost() const;																	//	OK	->Peu utile car les valeurs sont triées
//X		Solution& best_solution() const;															//	-	
//X		Solution& worst_solution() const;															//	-	

//X		void evolution();																			//	-	En attente des autres
		void trier();																				//	OK	QuickSort
		

	private:
		vector<Solution*> 		d_solutions;     													//		individuals in population
		vector<struct particle> d_fitnessValues;													//		
		const SetUpParams& 		d_setup;															//		
		int 					d_upperCost,d_lowerCost;											//		upper and lower fitness of individuals in population
																									//		->Peu utile car les valeurs sont triées
		
		int partition(int gauche, int droite);														//	OK	QuickSort
		void QuickSort(int gauche, int droite);														//	OK	QuickSort										
};

#endif
