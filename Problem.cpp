#include "Problem.h"

Problem(double lowLim, double upLim, int dim):
	_lowerLimit{lowLim},
	_upperLimit{upLim},
	_dimension{dim}
{
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
	return dimension;
}
