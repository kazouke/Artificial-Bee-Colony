#include "Problem.h"

Problem::Problem(double lowLim, double upLim, int dim):
	_lowerLimit{lowLim},
	_upperLimit{upLim},
	_dimension{dim}
{
}

std::ostream& operator<<(std::ostream& os, const Problem& pbm)
{
    os << pbm._lowerLimit << " " << pbm._upperLimit << " " << pbm._dimension;
    return os;
}
std::istream& operator>>(std::istream& is, Problem& pbm)
{
    is >> pbm._lowerLimit >> pbm._upperLimit >> pbm._dimension;
    return is;
}

double Problem::lowerLimit() const
{
	return _lowerLimit;
}

double Problem::upperLimit() const
{
	return _upperLimit;
}

int Problem::dimension() const
{
	return _dimension;
}
