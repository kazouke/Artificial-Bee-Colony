#include "Solution.h"

Solution::Solution (const Problem& pbm) : _solution{0}, _pbm{pbm} {
	_solution.resize(pbm.dimension());
}

//Solution::Solution (const Solution& sol) {}

Solution::~Solution() {}

std::ostream& operator<< (std::ostream& os, const Solution& sol) {
	os << sol._current_fitness;
    return os;
}

std::istream& operator>> (std::istream& is, Solution& sol) {
	is >> sol._current_fitness;
    return is;
}

const Problem& Solution::pbm() const {
	return _pbm;
}

Solution& Solution::operator= (const Solution& sol) {}

bool Solution::operator== (const Solution& sol) const {}

bool Solution::operator!= (const Solution& sol) const {}

void Solution::initialize() {
	for (int i = 0; i < _solution.size(); i++) {
		double r = 1.0*rand() / (RAND_MAX+1.0);
		_solution[i] = r * (_pbm.upperLimit() - _pbm.lowerLimit()) + _pbm.lowerLimit();
		std::cout << _solution[i] << std::endl;
	}
}

double Solution::fitness() {
	
}

double Solution::get_fitness() const {
	return _current_fitness;
}

unsigned int Solution::size() const {
	return _solition.size();
}

std::vector<double>& Solution::solution() {
	return _solution;
}

double& Solution::position(const int index) {
	return _solution[index];
}

void Solution::position(const int index, const double value) {
	_solution[index] = value;
}
