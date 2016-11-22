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

struct particle // index of a particle in the swarm and its fitness
{
    int index;
    double fitness;
};
  
class ABC
{
	public:
		ABC(const Problem& pbm,const SetUpParams& setup); 
		~ABC();

		const SetUpParams& setup() const;															// retourne les paramètres
	  	void initialize();	//Revoir																//
 
		// creates a array with fitness of all solutions in ABC and its position in the ABC
       void evaluate();	//Revoir																//
	 
	 	const vector<Solution*>& solutions() const;													//
		int upper_cost() const;																		//
		int lower_cost() const;																		//
		Solution& solution(const int index) const;													//
    	vector<struct particle>&  fitness_values();													//
		double fitness(const int index) const;														//
         
		 
		double best_cost() const;																	//
		double worst_cost() const;																	//

		void trier();		// trie croissant des solutions par rapport à la fitness
		int imin(int i) const;
		
		void launch();	//lance l'algo ABC

	private:
		vector<Solution*> 		d_solutions;     													// individuals in population
		vector<struct particle> d_fitnessValues;													//
		const SetUpParams& 		d_setup;															//
		int 					d_upperCost,d_lowerCost;											// upper and lower fitness of individuals in population
};

#endif
