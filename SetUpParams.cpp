#include "SetUpParams.h"

//Constructeur
SetUpParams::SetUpParams(int nbRuns, int nbEvoSteps, int popSize, int solSize) :
    _independent_runs{nbRuns},
    _nb_evolution_steps{nbEvoSteps},
    _population_size{popSize},
    _solution_size{solSize}
{}

//Surcharges
std::ostream& operator<<(std::ostream& os, const SetUpParams& setup)
{
    os << setup._independent_runs << " " << setup._nb_evolution_steps << " " << setup._population_size << " " << setup._solution_size;
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

//Setters
void SetUpParams::independent_runs(const unsigned int val)
{
	_independent_runs = val;
}
void SetUpParams::nb_evolution_steps(const unsigned int val)
{
	_nb_evolution_steps = val;
}
void SetUpParams::population_size(const unsigned int val)
{
	_population_size = val;
}
void SetUpParams::solution_size(const unsigned int val)
{
	_solution_size = val;
}
