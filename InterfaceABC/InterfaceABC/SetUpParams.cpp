#include "SetUpParams.h"

//Constructeur
SetUpParams::SetUpParams(int nbRuns, int nbEvoSteps, int popSize, int solSize) :
_independent_runs{ nbRuns },
_nb_evolution_steps{ nbEvoSteps },
_population_size{ popSize },
_solution_size{ solSize }
{}

SetUpParams::SetUpParams(const SetUpParams & setup) :
_independent_runs{ setup._independent_runs },
_nb_evolution_steps{ setup._nb_evolution_steps },
_population_size{ setup._population_size },
_solution_size{ setup._solution_size }
{}


//Surcharges
std::ostream& operator<<(std::ostream& os, const SetUpParams& setup)
{
	os << "Params nbrun " << setup._independent_runs << " nbevolution " << setup._nb_evolution_steps << " popsize " << setup._population_size << " solsize " << setup._solution_size;
	return os;
}
std::istream& operator>>(std::istream& is, SetUpParams& setup)
{
	is >> setup._independent_runs >> setup._nb_evolution_steps >> setup._population_size >> setup._solution_size;
	return is;
}

//Getters
const unsigned int SetUpParams::independent_runs() const
{
	return _independent_runs;
}
const unsigned int SetUpParams::nb_evolution_steps() const
{
	return _nb_evolution_steps;
}
const unsigned int SetUpParams::population_size() const
{
	return _population_size;
}
const unsigned int SetUpParams::solution_size() const
{
	return _solution_size;
}

