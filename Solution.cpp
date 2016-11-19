#include "Solution.h"

Solution::Solution (const Problem& pbm) : _solution{0}, _current_fitness{INT_MAX}, _pbm{pbm} {
	_solution.resize(pbm.dimension());
}

Solution::Solution (const Solution& sol) : _solution{sol._solution}, _current_fitness{sol._current_fitness}, _pbm{sol._pbm} {}

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

Solution& Solution::operator= (const Solution& sol) {
	_solution = sol._solution;
	_current_fitness = sol._current_fitness;
}

bool Solution::operator== (const Solution& sol) const {
	return _solution == sol._solution && _current_fitness == sol._current_fitness && _pbm == sol._pbm;
}

bool Solution::operator!= (const Solution& sol) const {
	return !(*this == sol);
}

void Solution::initialize() {
	for (int i = 0; i < _solution.size(); i++) {
		double r = 1.0*rand() / (RAND_MAX+1.0);
		_solution[i] = r * (_pbm.upperLimit() - _pbm.lowerLimit()) + _pbm.lowerLimit();
	}
}

double Solution::fitness() {
	
}

double Solution::get_fitness() const {
	return _current_fitness;
}

unsigned int Solution::size() const {
	return _solution.size();
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
