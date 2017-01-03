#ifndef PROBLEM_H
#define PROBLEM_H
#include <iostream>
#include <vector>

typedef double(*Fonction)(const std::vector<double>&);

class Problem
{
public:
	Problem() = delete;
	Problem(double lowLim, double upLim, int dim, Fonction f);
	~Problem() = default;

	friend std::ostream& operator<< (std::ostream& os, const Problem& pbm);
	friend std::istream& operator>> (std::istream& is, Problem& pbm);

	Problem& operator=  (const Problem& pbm);
	bool operator== (const Problem& pbm) const;
	bool operator!= (const Problem& pbm) const;

	//Direction direction () const; //Maximize or Minimize
	double lowerLimit() const;
	double upperLimit() const;
	int dimension() const;
	Fonction f() const;
private:

	double _lowerLimit, _upperLimit;
	int _dimension;
	Fonction _fonction;
};

#endif
