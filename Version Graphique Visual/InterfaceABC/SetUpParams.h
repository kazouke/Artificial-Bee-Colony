#ifndef SETUPPARAMS_H
#define SETUPPARAMS_H
#include <iostream>

class SetUpParams
{
	//Initialisation des paramètres de l'algorithme ABC

private:
	unsigned int   _independent_runs;         //number of independent runs
	unsigned int   _nb_evolution_steps;       // number of iterations per run
	unsigned int   _population_size;		// number of solutions in the population
	unsigned int   _solution_size;	        // size of each particle
	unsigned int _max_trial;				//max number of trials

public:
	SetUpParams() = delete;
	SetUpParams(unsigned int nbRuns, unsigned int nbEvoSteps, unsigned int popSize, unsigned int solSize, unsigned int maxTrial);
	SetUpParams(const SetUpParams & setup);
	~SetUpParams() = default;


	friend std::ostream& operator<< (std::ostream& os, const SetUpParams& setup);
	friend std::istream& operator>> (std::istream& is, SetUpParams& setup);

	const unsigned int   independent_runs() const;
	const unsigned int   nb_evolution_steps() const;
	const unsigned int   population_size() const;
	const unsigned int   solution_size() const;
	const unsigned int   max_trial() const;

};

#endif
