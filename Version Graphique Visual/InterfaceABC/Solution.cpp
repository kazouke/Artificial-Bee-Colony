#include "Solution.h"

Solution::Solution(const Problem& pbm) : _solution{}, _current_fitness{ INT_MAX }, _function_fitness{ INT_MAX }, _pbm{ pbm }, d_trial{ 0 } {
	_solution.resize(pbm.dimension());
	initialize();
}

Solution::Solution(const Solution& sol) : _solution{}, _current_fitness{ sol._current_fitness }, _function_fitness{ sol._function_fitness }, _pbm{ sol._pbm }, d_trial{ 0 } {
	_solution = sol._solution;
}

Solution::~Solution() {}

std::ostream& operator<< (std::ostream& os, const Solution& sol) {
	os << sol._current_fitness;
	return os;
}

std::istream& operator >> (std::istream& is, Solution& sol) {
	is >> sol._current_fitness;
	return is;
}

const Problem& Solution::pbm() const {
	return _pbm;
}

Solution& Solution::operator= (const Solution& sol) {
	_solution = sol._solution;
	_current_fitness = sol._current_fitness;
	_function_fitness = sol._function_fitness;
	return *(this);
}

bool Solution::operator== (const Solution& sol) const {
	return _solution == sol._solution && _current_fitness == sol._current_fitness  && _function_fitness == sol._function_fitness && _pbm == sol._pbm;
}

bool Solution::operator!= (const Solution& sol) const {
	return !(*this == sol);
}

void Solution::initialize() {
	for (int i = 0; i < _solution.size(); i++) {
		double r = 1.0*rand() / RAND_MAX;
		_solution[i] = r * (_pbm.upperLimit() - _pbm.lowerLimit()) + _pbm.lowerLimit();
	}


	_function_fitness = (_pbm.f())(_solution);
	_current_fitness = CalculateFitness(_function_fitness);

	d_trial = 0;
}

double Solution::FunctionFitness() {
	return _function_fitness;
}

double Solution::SolutionFitness() {
	return (_pbm.f())(_solution);
}

unsigned int Solution::size() const {
	return _solution.size();
}

std::vector<double>& Solution::solution() {
	return _solution;
}

double Solution::position(const int index) const {
	return _solution[index];
}

void Solution::position(const int index, const double value) {
	_solution[index] = value;
}

double Solution::maxSol() const {
	double max = _solution[0];
	if (max<0) max *= -1;
	for (int i = 1; i < _solution.size(); i++)
	{
		if (_solution[i] > max) max = _solution[i];
		if (_solution[i] * -1 > max) max = _solution[i] * -1;
	}
	return max;
}

void Solution::incrementerTrial()
{
	d_trial++;
}

int Solution::trial() const
{
	return d_trial;
}

double Solution::CalculateFitness(double fun)
{
	double result = 0;
	if (fun >= 0)
	{
		result = 1 / (fun + 1);
	}
	else
	{
		result = 1 + abs(fun);
	}
	return result;
}
