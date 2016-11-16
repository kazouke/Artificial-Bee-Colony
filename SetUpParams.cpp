#include "SetUpParams.h"

SetUpParams::SetUpParams(int nbRuns, int nbEvoSteps, int popSize, int solSize) :
    _independent_runs(nbRuns),
    _nb_evolution_steps(nbEvoSteps),
    _population_size(popSize),
    _solution_size(solSize)
{}


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
