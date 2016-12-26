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
		/*! \brief Constructor
    	* MyAlgorithm class Constructor
    	* \param[in] pbm : Probl�me
    	* \param[in] setup : Options
    	*/
		ABC(const Problem& pbm,const SetUpParams& setup); 											//	OK
		
		/*! \brief Destructor
    	* MyAlgorithm class Destructor
    	*/
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
		const SetUpParams& setup() const;															//	OK	retourne les param�tres
		
		//-----------------Boucle---------------------------------------
		/*! \brief Evolution
    	* MyAlgorithm class Evolution
    	*/
		double evolution();																			//	OK	Boucle principale
		/*! \brief Initialize
    	* MyAlgorithm class Initialize
    	*/
		void initialize();																			//	OK	Renouvelle les solutions, calcule la fitness associée et les tri croissant par fitness
		/*! \brief Initialize
    	* MyAlgorithm class Initialize
    	*/
		void sendEmployedBees();																	//	OK
		/*! \brief SendOnLookerBees
    	* MyAlgorithm class SendOnLookerBees
    	* \param[in] probabilite : Probabilit�s de chaque source
    	*/
		void SendOnLookerBees(std::vector <int> probabilite);										//	OK
		/*! \brief CalculateProbabilities
    	* MyAlgorithm class CalculateProbabilities
    	*/
		std::vector <int> CalculateProbabilities() const;											//	OK
		/*! \brief sendScoutBees
    	* MyAlgorithm class sendScoutBees
    	*/
		void sendScoutBees();																		//	OK
		/*! \brief Evaluate
    	* MyAlgorithm class Evaluate
    	*/
		void evaluate();																			//	OK

	private:
		vector<Solution*> 		d_solutions;     													//		Abeilles 				d_setup.population_size
		vector<struct particle> d_fitnessValues;													//		Evaluation des abeilles	d_setup.population_size
		const SetUpParams 		d_setup;															//		Parametres
		int 					d_upperCost,d_lowerCost;											//		Position de la meilleur / pire fitness->Peu utile car les valeurs sont triées

		void trier();
		void BeesWork(int param2change,int i);														//	OK	QuickSort
		int partition(int gauche, int droite);														//	OK	QuickSort
		void QuickSort(int gauche, int droite);														//	OK	QuickSort
};

#endif
